//
//  Direct3DFramebufferToScreenGpuProgramWrapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/7/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DFramebufferToScreenGpuProgramWrapper__
#define __noctisgames__Direct3DFramebufferToScreenGpuProgramWrapper__

#include "GpuProgramWrapper.h"

#include "pch.h"

class Direct3DFramebufferToScreenGpuProgramWrapper : public GpuProgramWrapper
{
public:
	Direct3DFramebufferToScreenGpuProgramWrapper();

    virtual ~Direct3DFramebufferToScreenGpuProgramWrapper();
    
	virtual void bind();

	virtual void unbind();

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};

#endif /* defined(__noctisgames__Direct3DFramebufferToScreenGpuProgramWrapper__) */
