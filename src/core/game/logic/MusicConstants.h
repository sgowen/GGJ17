//
//  MusicConstants.h
//  ggj17
//
//  Created by Stephen Gowen on 1/17/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __ggj17__MusicConstants__
#define __ggj17__MusicConstants__

#define MUSIC_NONE 0 // Does Nothing
#define MUSIC_LOAD_DEMO 1

#define MUSIC_PLAY 1001 // Assuming music is loaded
#define MUSIC_PLAY_LOOP 1002 // Assuming music is loaded
#define MUSIC_PAUSE 1003
#define MUSIC_RESUME 1004
#define MUSIC_STOP 1005
#define MUSIC_SET_VOLUME 2000 // Passed in this format: [2][0-100], where the first digit is the action and the rest determines the volume (0-100), e.g. 2100 or 2050

#endif /* defined(__ggj17__MusicConstants__) */
