//
//  DeviceHelperFactory.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__DeviceHelperFactory__
#define __noctisgames__DeviceHelperFactory__

class IDeviceHelper;

#define DEVICE_HELPER_FACTORY (DeviceHelperFactory::getInstance())

class DeviceHelperFactory
{
public:
	static DeviceHelperFactory* getInstance();
    
    IDeviceHelper* createDeviceHelper();

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    DeviceHelperFactory() {}
    DeviceHelperFactory(const DeviceHelperFactory&);
    DeviceHelperFactory& operator=(const DeviceHelperFactory&);
};

#endif /* defined(__noctisgames__DeviceHelperFactory__) */
