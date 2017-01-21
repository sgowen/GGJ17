//
//  server.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/5/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__server__
#define __noctisgames__server__

#define MAX_DATA_SIZE 512 // max number of bytes we can get at once

int startServerUDP();

const char * readFromClient(char * buffer); // Returns client id

int writeToClients(const char * buffer); // Returns 1 for success, -1 otherwise

void shutDownServer();

void runServer();

#endif /* defined(__noctisgames__server__) */
