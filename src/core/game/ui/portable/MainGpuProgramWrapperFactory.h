//
//  MainGpuProgramWrapperFactory.h
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__MainGpuProgramWrapperFactory__
#define __noctisgames__MainGpuProgramWrapperFactory__

class SinWaveTextureGpuProgramWrapper;

#define MAIN_GPU_PROGRAM_WRAPPER_FACTORY (MainGpuProgramWrapperFactory::getInstance())

class MainGpuProgramWrapperFactory
{
public:
	static MainGpuProgramWrapperFactory* getInstance();
    
    SinWaveTextureGpuProgramWrapper* createSinWaveTextureGpuProgramWrapper();

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    MainGpuProgramWrapperFactory() {}
    MainGpuProgramWrapperFactory(const MainGpuProgramWrapperFactory&);
    MainGpuProgramWrapperFactory& operator=(const MainGpuProgramWrapperFactory&);
};

#endif /* defined(__noctisgames__MainGpuProgramWrapperFactory__) */
