//
//  asset_utils.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__asset_utils__
#define __noctisgames__asset_utils__

#include "platform_gl.h"
#include "image.h"

RawImageData load_png_asset(const char* relative_path);

GLuint load_png_asset_into_texture(RawImageData raw_image_data, int repeat_s);

GLuint build_program_from_assets(const char* vertex_shader_path, const char* fragment_shader_path);

#endif /* defined(__noctisgames__asset_utils__) */
