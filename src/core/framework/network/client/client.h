//
//  client.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/5/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__client__
#define __noctisgames__client__

#define MAX_DATA_SIZE 512 // max number of bytes we can get at once

void updateTouchPos(float x, float y);

char * getLatestMessage();

int getClientStatus();

int startClientUDP();

int sendTouchInput();

int readFromServer();

void shutDownClient();

void testMessage();

#endif /* defined(__noctisgames__client__) */
