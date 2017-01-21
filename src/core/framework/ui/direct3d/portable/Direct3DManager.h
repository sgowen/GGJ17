//
//  Direct3DManager.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/17/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DManager__
#define __noctisgames__Direct3DManager__

#define VERTICES_PER_LINE 2
#define VERTICES_PER_RECTANGLE 4
#define INDICES_PER_RECTANGLE 6

#define D3DManager (Direct3DManager::getInstance())

#include "Direct3DProgram.h"
#include "DeviceResources.h"

#include <vector>
#include <memory>

class Direct3DTextureGpuProgramWrapper;
class Direct3DGeometryGpuProgramWrapper;
class Direct3DFramebufferToScreenGpuProgramWrapper;

class Direct3DManager
{
public:
	static void setDeviceResources(DX::DeviceResources* deviceResources);

	static DX::DeviceResources* getDeviceResources();

    static void create();
    
    static void destroy();
    
    static Direct3DManager * getInstance();
    
    void createDeviceDependentResources(int maxBatchSize);
    
    void createWindowSizeDependentResources(int screenWidth, int screenHeight, int numFramebuffers);
    
    void releaseDeviceDependentResources();

	void updateMatrix(float left, float right, float bottom, float top);

	// Called by Batchers
	void addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a, float u, float v); 
	void addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a);
    
    void useNormalBlending();
    void useScreenBlending();
    
	std::vector<ID3D11Texture2D*>& getOffscreenRenderTargets();
	std::vector<ID3D11RenderTargetView*>& getOffscreenRenderTargetViews();
	std::vector<ID3D11ShaderResourceView*>& getOffscreenShaderResourceViews();
	Microsoft::WRL::ComPtr<ID3D11BlendState>& getBlendState();
	Microsoft::WRL::ComPtr<ID3D11BlendState>& getScreenBlendState();
	Microsoft::WRL::ComPtr<ID3D11Buffer>& getMatrixConstantbuffer();
	Microsoft::WRL::ComPtr<ID3D11Buffer>& getIndexbuffer();
	Microsoft::WRL::ComPtr<ID3D11SamplerState>& getSbSamplerState();
	Microsoft::WRL::ComPtr<ID3D11SamplerState>& getSbWrapSamplerState();
	Microsoft::WRL::ComPtr<ID3D11Buffer>& getSbVertexBuffer();
	std::vector<TEXTURE_VERTEX>& getTextureVertices();
	Microsoft::WRL::ComPtr<ID3D11Buffer>& getGbVertexBuffer();
	std::vector<COLOR_VERTEX>& getColorVertices();
	DirectX::XMFLOAT4X4& getMatFinal();

private:
    static Direct3DManager* s_pInstance;
    
	// Cached pointer to device resources.
	static DX::DeviceResources* s_pDeviceResources;

	std::vector<ID3D11Texture2D*> m_offscreenRenderTargets; // the offscreen render target texture
	std::vector<ID3D11RenderTargetView*> m_offscreenRenderTargetViews; // the offscreen render target interface
	std::vector<ID3D11ShaderResourceView*> m_offscreenShaderResourceViews; // this is needed for the screen pixel shader
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState; // the blend state interface
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_screenBlendState; // the blend state interface, but for rendering to the screen
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_matrixConstantbuffer; // the matrix constant buffer interface
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexbuffer; // the index buffer interface

	// Used in SpriteBatcher
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sbSamplerState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sbWrapSamplerState;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_sbVertexBuffer;
	std::vector<TEXTURE_VERTEX> m_textureVertices;

	// Used in NGRectBatcher, LineBatcher, and CircleBatcher (Geometry)
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_gbVertexBuffer; // the vertex buffer interface
	std::vector<COLOR_VERTEX> m_colorVertices;

	// All above rendering takes place inside this matrix
	DirectX::XMFLOAT4X4 m_matFinal;
    
    int m_iScreenWidth;
    int m_iScreenHeight;
	int m_iNumFramebuffers;

	void createBlendStates();
	void createSamplerStates();
	void createVertexBufferForSpriteBatcher(int maxBatchSize);
	void createVertexBufferForGeometryBatchers(int maxBatchSize);
	void createIndexBuffer(int maxBatchSize);
	void createConstantBuffer();

	std::vector<short> createIndexValues(int maxBatchSize);
    void createFramebufferObjects();
    void createFramebufferObject();
    void releaseFramebuffers();

	// ctor, copy ctor, and assignment should be private in a Singleton
	Direct3DManager();
    ~Direct3DManager();
	Direct3DManager(const Direct3DManager&);
	Direct3DManager& operator=(const Direct3DManager&);
};

#endif /* defined(__noctisgames__Direct3DManager__) */
