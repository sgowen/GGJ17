//
//  Direct3DTextureGpuProgramWrapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/30/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DTextureGpuProgramWrapper__
#define __noctisgames__Direct3DTextureGpuProgramWrapper__

#include "GpuProgramWrapper.h"

#include "pch.h"

class Direct3DTextureGpuProgramWrapper : public GpuProgramWrapper
{
public:
	Direct3DTextureGpuProgramWrapper();
    
    virtual ~Direct3DTextureGpuProgramWrapper();

	virtual void bind();

	virtual void unbind();

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
};

#endif /* defined(__noctisgames__Direct3DTextureGpuProgramWrapper__) */
