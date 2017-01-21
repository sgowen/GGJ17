//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Direct3DManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "MusicConstants.h"
#include "SoundConstants.h"
#include "macros.h"
#include "GamePadEventType.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() : m_screen(nullptr), m_isPointerPressed(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
	if (m_audEngine)
	{
		m_audEngine->Suspend();
	}

	m_musicLoop.reset();

	for (std::vector<std::unique_ptr<DirectX::SoundEffectInstance>>::iterator i = m_activeSounds.begin(); i != m_activeSounds.end(); i++)
	{
		(*i).reset();
	}

	delete m_screen;

	m_deviceResources.reset();
}

// Initialize the Direct3D resources required to run.
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
void Game::Initialize(HWND window, int width, int height)
{
	m_deviceResources->SetWindow(window, width, height);
#else
void Game::Initialize(IUnknown* window, int width, int height, float dpi, DXGI_MODE_ROTATION rotation)
{
	m_fDPI = dpi;
	m_deviceResources->SetWindow(window, width, height, rotation);
#endif

    m_deviceResources->CreateDeviceResources();

	Direct3DManager::setDeviceResources(m_deviceResources.get());

	m_screen = new MainScreen();
	m_screen->onResume();

    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_gamePad = std::make_unique<GamePad>();
	
	// Use MODE_RELATIVE for displaying your own mouse pointer (like Diablo or Age of Empires)
	m_mouse->SetMode(Mouse::MODE_ABSOLUTE);

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
	m_mouse->SetWindow(window);
#else
	m_keyboard->SetWindow(reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(window));
	m_mouse->SetWindow(reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(window));
#endif

	initSoundEngine();
}

void Game::OnNewAudioDevice()
{
	m_retryAudio = true;
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	auto kb = m_keyboard->GetState();
	if (kb.Escape)
	{
		ExitGame();
	}

	auto mouse = m_mouse->GetState();
	if (mouse.positionMode == Mouse::MODE_ABSOLUTE)
	{
		if (m_isPointerPressed && mouse.leftButton)
		{
			INPUT_MANAGER->onTouch(DRAGGED, float(mouse.x), float(mouse.y));
		}
		else if (mouse.leftButton && !m_isPointerPressed)
		{
			INPUT_MANAGER->onTouch(DOWN, float(mouse.x), float(mouse.y));

			m_isPointerPressed = true;
		}
		else if (m_isPointerPressed && !mouse.leftButton)
		{
			INPUT_MANAGER->onTouch(UP, float(mouse.x), float(mouse.y));

			m_isPointerPressed = false;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		auto gamePadState = m_gamePad->GetState(i);
		if (gamePadState.IsConnected())
		{
			if (gamePadState.IsViewPressed())
			{
				PostQuitMessage(0);
			}

			m_buttons.Update(gamePadState);
			if (m_buttons.a == GamePad::ButtonStateTracker::PRESSED)
			{
				// A was up last frame, it just went down this frame
			}
			if (m_buttons.b == GamePad::ButtonStateTracker::RELEASED)
			{
				// B was down last frame, it just went up this frame
			}

			INPUT_MANAGER->onGamePadInput(STICK_LEFT, i, gamePadState.thumbSticks.leftX / 10, gamePadState.thumbSticks.leftY / 10);
			INPUT_MANAGER->onGamePadInput(STICK_RIGHT, i, gamePadState.thumbSticks.leftX / 10, gamePadState.thumbSticks.rightY / 10);
			INPUT_MANAGER->onGamePadInput(TRIGGER, i, gamePadState.triggers.left, gamePadState.triggers.right);

			if (m_buttons.leftTrigger == GamePad::ButtonStateTracker::PRESSED
				|| m_buttons.leftTrigger == GamePad::ButtonStateTracker::HELD)
			{
				
			}
		}
	}

	if (m_retryAudio)
	{
		m_retryAudio = false;
		if (m_audEngine->Reset())
		{
			// TODO: restart any looped sounds here
		}
	}
	else if (!m_audEngine->Update())
	{
		if (m_audEngine->IsCriticalError())
		{
			m_retryAudio = true;
		}
	}

	beginPixEvent(L"Update");

	float elapsedTime = float(timer.GetElapsedSeconds());

	m_screen->update(elapsedTime);

	endPixEvent();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

	beginPixEvent(L"Render", m_deviceResources.get());

	m_screen->render();

    endPixEvent(m_deviceResources.get());

	handleSound();
	handleMusic();

    // Show the new frame.
	beginPixEvent(L"Present");
    m_deviceResources->Present();
	endPixEvent();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	beginPixEvent(L"Clear", m_deviceResources.get());

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	endPixEvent(m_deviceResources.get());
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"OnActivated");
#endif

	m_gamePad->Resume();
	m_buttons.Reset();

    // TODO: Game is becoming active window.
	m_screen->onResume();
}

void Game::OnDeactivated()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"OnDeactivated");
#endif

	m_gamePad->Suspend();
	m_buttons.Reset();

    // TODO: Game is becoming background window.
	m_screen->onPause();
}

void Game::OnSuspending()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"OnSuspending");
#endif

	m_gamePad->Suspend();

	// TODO: Game is being power-suspended (or minimized).
	m_audEngine->Suspend();

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
	// Empty
#else
	auto context = m_deviceResources->GetD3DDeviceContext();
	context->ClearState();

	m_deviceResources->Trim();
#endif

	m_screen->onPause();
}

void Game::OnResuming()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"OnResuming");
#endif

	m_gamePad->Resume();

	// TODO: Game is being power-resumed (or returning from minimize).
	m_timer.ResetElapsedTime();
	
	m_audEngine->Resume();

	m_screen->onResume();
}

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
	{
		return;
	}

	CreateWindowSizeDependentResources();
}
#else
void Game::OnWindowSizeChanged(int width, int height, float dpi, DXGI_MODE_ROTATION rotation)
{
#if defined(_DEBUG)
	OutputDebugStringW(L"OnWindowSizeChanged");
#endif

	m_fDPI = dpi;

	if (!m_deviceResources->WindowSizeChanged(width, height, rotation))
	{
		return;
	}

	CreateWindowSizeDependentResources();
}

void Game::ValidateDevice()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"ValidateDevice");
#endif

	m_deviceResources->ValidateDevice();
}
#endif

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"CreateDeviceDependentResources");
#endif

	m_screen->createDeviceDependentResources();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"CreateWindowSizeDependentResources");
#endif

	RECT outputSize = m_deviceResources->GetOutputSize();
	LONG width = outputSize.right - outputSize.left;
	LONG height = outputSize.bottom - outputSize.top;

	int touchScreenWidth;
	int touchScreenHeight;
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
	touchScreenWidth = width;
	touchScreenHeight = height;
#else
	// Landscape
	touchScreenWidth = ConvertPixelsToDips(height);
	touchScreenHeight = ConvertPixelsToDips(width);
#endif

	m_screen->createWindowSizeDependentResources(width, height, touchScreenWidth, touchScreenHeight);
}

void Game::beginPixEvent(PCWSTR pFormat, DX::DeviceResources* deviceResources)
{
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
	UNUSED(deviceResources);

	m_deviceResources->PIXBeginEvent(pFormat);
#else
	if (deviceResources)
	{
		auto context = deviceResources->GetD3DDeviceContext();
		PIXBeginEvent(context, PIX_COLOR_DEFAULT, pFormat);
	}
	else
	{
		PIXBeginEvent(PIX_COLOR_DEFAULT, pFormat);
	}
#endif
}

void Game::endPixEvent(DX::DeviceResources* deviceResources)
{
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
	UNUSED(deviceResources);

	m_deviceResources->PIXEndEvent();
#else
	if (deviceResources)
	{
		auto context = deviceResources->GetD3DDeviceContext();
		PIXEndEvent(context);
	}
	else
	{
		PIXEndEvent();
	}
#endif
}

void Game::OnDeviceLost()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"OnDeviceLost");
#endif

	m_screen->releaseDeviceDependentResources();
}

void Game::OnDeviceRestored()
{
#if defined(_DEBUG)
	OutputDebugStringW(L"OnDeviceRestored");
#endif

	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion

#pragma region Audio
void Game::handleSound()
{
	short rawSoundId;
	short playerIndex;
	short soundId;
	while ((rawSoundId = SOUND_MANAGER->getCurrentSoundId()) > SOUND_NONE)
	{
		playerIndex = 0;
		while (rawSoundId >= 10000)
		{
			rawSoundId -= 10000;
			playerIndex++;
		}

		soundId = 0;
		while (rawSoundId >= 1000)
		{
			rawSoundId -= 1000;
			soundId++;
		}

		playMultiSound(playerIndex, soundId, (rawSoundId / 100.0f));
	}
}

void Game::handleMusic()
{
	short musicId;
    while ((musicId = SOUND_MANAGER->getCurrentMusicId()) > MUSIC_NONE)
    {
		if (musicId > MUSIC_SET_VOLUME)
		{
			if (m_musicLoop)
			{
				m_musicLoop->SetVolume((musicId % 1000) / 100.0f);
			}
		}
		else
		{
			switch (musicId)
			{
			case MUSIC_LOAD_DEMO:
				loadMusic(L"music_demo.wav");
				break;
			case MUSIC_PLAY:
				if (m_musicLoop)
				{
					m_musicLoop->Play();
				}
				break;
			case MUSIC_PLAY_LOOP:
				if (m_musicLoop)
				{
					m_musicLoop->Play(true);
				}
				break;
			case MUSIC_PAUSE:
				if (m_musicLoop)
				{
					m_musicLoop->Pause();
				}
				break;
			case MUSIC_RESUME:
				if (m_musicLoop)
				{
					m_musicLoop->Resume();
				}
				break;
			case MUSIC_STOP:
				if (m_musicLoop)
				{
					m_musicLoop->Stop();
				}
				break;
			}
		}
	}
}

void Game::playSound(int soundId, bool isLooping)
{
	// TODO
}

void Game::playSound(int soundId)
{
	m_sounds.at(soundId - 1)->Play();
}

void Game::playMultiSound(int playerIndex, int soundId, float volume)
{
	int finalIndex = soundId - 1 + playerIndex;
	if (finalIndex < m_activeSounds.size())
	{
		if (m_activeSounds.at(finalIndex)->GetState() == PLAYING)
		{
			m_activeSounds.at(finalIndex)->SetVolume(volume);
		}
		else
		{
			m_activeSounds.at(finalIndex)->Play(volume);
		}
	}
}

void Game::stopSound(int soundId)
{
	// TODO
}

void Game::stopAllSounds()
{
	// TODO
}

void Game::stopAllLoopingSounds()
{
	// TODO
}

void Game::initSoundEngine()
{
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	m_audEngine = std::make_unique<AudioEngine>(eflags);
	m_retryAudio = false;

	loadMultiSound(L"sound_store.wav");
	loadMultiSound(L"sound_release.wav");
}

void Game::loadSound(const wchar_t* waveFileName)
{
	m_sounds.push_back(std::make_unique<SoundEffect>(m_audEngine.get(), waveFileName));
}

void Game::loadMultiSound(const wchar_t* waveFileName)
{
	std::unique_ptr<DirectX::SoundEffect> se = std::make_unique<SoundEffect>(m_audEngine.get(), waveFileName);
	m_activeSounds.push_back(se->CreateInstance());
	m_activeSounds.push_back(se->CreateInstance());
	m_activeSounds.push_back(se->CreateInstance());
	m_activeSounds.push_back(se->CreateInstance());
	m_sounds.push_back(se);
}

void Game::loadMusic(const wchar_t* waveFileName)
{
	m_music.reset();
	m_music = std::make_unique<SoundEffect>(m_audEngine.get(), waveFileName);

	m_musicLoop.reset();
	m_musicLoop = m_music->CreateInstance();
}
#pragma endregion

// Exit helper
void ExitGame()
{
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
	PostQuitMessage(0);
#else
	Windows::ApplicationModel::Core::CoreApplication::Exit();
#endif
}
