//
//  platform_asset_utils.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__platform_asset_utils__
#define __noctisgames__platform_asset_utils__

#include "platform_file_utils.h"

FileData get_asset_data(const char* relative_path);

void release_asset_data(const FileData* file_data);

#endif /* defined(__noctisgames__platform_asset_utils__) */
