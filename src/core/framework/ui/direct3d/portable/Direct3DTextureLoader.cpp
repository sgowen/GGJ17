//
//  Direct3DTextureLoader.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Direct3DTextureLoader.h"

#include "pch.h"
#include "DDSTextureLoader.h"
#include "macros.h"
#include "Direct3DManager.h"
#include "GpuTextureDataWrapper.h"
#include "GpuTextureWrapper.h"
#include "PlatformHelpers.h"

#include <string>

Direct3DTextureLoader::Direct3DTextureLoader() : ITextureLoader()
{
    // Empty
}

GpuTextureDataWrapper* Direct3DTextureLoader::loadTextureData(const char* textureName)
{
    size_t len = strlen(textureName);
    
    char* textureFileName = new char[8 + len + 5];
    
    strcpy(textureFileName, textureName);
    textureFileName[len] = '.';
    textureFileName[len + 1] = 'd';
    textureFileName[len + 2] = 'd';
    textureFileName[len + 3] = 's';
    textureFileName[len + 4] = '\0';
    
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, textureFileName, -1, wString, 4096);
    
    ID3D11ShaderResourceView *pShaderResourceView;
    
	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();
    DirectX::ThrowIfFailed(CreateDDSTextureFromFile(deviceResources->GetD3DDevice(), wString, nullptr, &pShaderResourceView));
    
    GpuTextureDataWrapper* tdw = new GpuTextureDataWrapper(pShaderResourceView);
    
    delete wString;
    delete textureFileName;
    
    return tdw;
}

GpuTextureWrapper* Direct3DTextureLoader::loadTexture(GpuTextureDataWrapper* textureData, int repeatS)
{
    UNUSED(repeatS);
    
    return new GpuTextureWrapper(textureData->texture);
}
