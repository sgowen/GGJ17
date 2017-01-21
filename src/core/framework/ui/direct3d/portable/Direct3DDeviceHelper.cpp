//
//  Direct3DDeviceHelper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Direct3DDeviceHelper.h"

#include "pch.h"
#include "Direct3DManager.h"

Direct3DDeviceHelper::Direct3DDeviceHelper() : IDeviceHelper()
{
    Direct3DManager::create();
}

Direct3DDeviceHelper::~Direct3DDeviceHelper()
{
    Direct3DManager::destroy();
}

void Direct3DDeviceHelper::createDeviceDependentResources(int maxBatchSize)
{
    D3DManager->createDeviceDependentResources(maxBatchSize);
}

void Direct3DDeviceHelper::createWindowSizeDependentResources(int screenWidth, int screenHeight, int numFramebuffers)
{
    D3DManager->createWindowSizeDependentResources(screenWidth, screenHeight, numFramebuffers);
}

void Direct3DDeviceHelper::releaseDeviceDependentResources()
{
    D3DManager->releaseDeviceDependentResources();
}
