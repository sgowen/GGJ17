//
//  DeviceHelperFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "DeviceHelperFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

DeviceHelperFactory* DeviceHelperFactory::getInstance()
{
    static DeviceHelperFactory *instance = new DeviceHelperFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
#include "OpenGLDeviceHelper.h"
IDeviceHelper* DeviceHelperFactory::createDeviceHelper() { return new OpenGLDeviceHelper(); }
#elif defined _WIN32
#include "Direct3DDeviceHelper.h"
IDeviceHelper* DeviceHelperFactory::createDeviceHelper() { return new Direct3DDeviceHelper(); }
#endif
