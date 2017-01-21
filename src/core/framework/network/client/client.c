//
//  client.c
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/5/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__

#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#elif defined _WIN32

#define bzero(b,len) memset(b, '\0', len)
#define bcopy(b1,b2,len) memcpy(b2, b1, len)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#endif

#define PORT "9999" // the port client will be connecting to

// get sockaddr, IPv4 or IPv6:
void * get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void error(const char *msg)
{
    perror(msg);
}

static volatile float xPos = 0;
static volatile float yPos = 0;

void updateTouchPos(float x, float y)
{
    xPos = x;
    yPos = y;
}

char latestMessage[MAX_DATA_SIZE];

char * getLatestMessage()
{
    return &latestMessage;
}

int clientStatus = 0;
int getClientStatus()
{
    return clientStatus;
}

#ifdef _WIN32
SOCKET sockfd;
size_t numbytes;
#else
int sockfd;
ssize_t numbytes;
#endif
struct addrinfo hints, *servinfo, *servinforead, *p;
int rv;
char buffer[MAX_DATA_SIZE];
struct sockaddr_storage server_addr;
socklen_t addr_len;
char s[INET6_ADDRSTRLEN];
char CLIENT_GUID[40];

int startClientUDP()
{
#ifdef _WIN32
    sockfd = INVALID_SOCKET;
    int wsaResult;
    WSADATA wsaData;
    
    // Initialize Winsock
    if ((wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup failed with error: %d\n", wsaResult);
        return -1;
    }
#endif
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    
    srand ((unsigned int)clock());
    char *szHex = "0123456789ABCDEF-";
    
#if defined __ANDROID__
    bzero(CLIENT_GUID, 40);
	CLIENT_GUID[0] = szHex[rand () % 16];
    CLIENT_GUID[1] = szHex[rand () % 16];
    CLIENT_GUID[2] = szHex[rand () % 16];
    CLIENT_GUID[3] = szHex[rand () % 16];
#else
    int t = 0;
    char *szTemp = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    unsigned long nLen = strlen (szTemp);
    
    for (t=0; t<nLen+1; t++)
    {
        int r = rand () % 16;
        char c = ' ';
        
        switch (szTemp[t])
        {
            case 'x' : { c = szHex [r]; } break;
            case 'y' : { c = szHex [(r & 0x03) | 0x08]; } break;
            case '-' : { c = '-'; } break;
            case '4' : { c = '4'; } break;
        }
        
		CLIENT_GUID[t] = ( t < nLen ) ? c : 0x00;
    }
#endif
    
    printf("Generated Client GUID: %s\n", CLIENT_GUID);
    
    static const char * hostname = "208.97.168.138";
//        static const char * hostname = "10.0.0.98"; // my computer
    if ((rv = getaddrinfo(hostname, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }
    
    // loop through all the results and make a socket
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("talker: socket");
            continue;
        }
        
        break;
    }
    
    if (p == NULL)
    {
        fprintf(stderr, "talker: failed to create socket\n");
        
#ifdef _WIN32
        WSACleanup();
#endif
        return -1;
    }
    
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);
    
#ifdef _WIN32
	DWORD dwTime = 100;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &dwTime, sizeof(dwTime)) < 0)
	{
		perror("talker: setsockopt");

		return -1;
	}
#else
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100000;

	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
	{
		perror("talker: setsockopt");

		return -1;
	}
#endif
    
    addr_len = sizeof server_addr;
    
    clientStatus = 1;
    
    return 1;
}

int sendTouchInput()
{
    clientStatus = 2;
    
    bzero(buffer, MAX_DATA_SIZE);
    
    int xPosInt = xPos * 100;
    int yPosInt = yPos * 100;
    
    printf("client: sending xPos: %f and yPos: %f as xPosInt: %d and yPosInt: %d\n", xPos, yPos, xPosInt, yPosInt);
    
    sprintf(buffer, "%s,%d,%d", CLIENT_GUID, xPosInt, yPosInt);
    unsigned long len = strlen(buffer);
    buffer[len] = '\0';
    
    if ((numbytes = sendto(sockfd, buffer, strlen(buffer), 0, p->ai_addr, p->ai_addrlen)) == -1)
    {
        perror("talker: sendto");
        
		shutDownClient();

        return -1;
    }
    
    printf("talker: sent %zd bytes\n", numbytes);
    
    clientStatus = 3;
    
    return 1;
}

int readFromServer()
{
    clientStatus = 4;
    
    if ((numbytes = recvfrom(sockfd, buffer, MAX_DATA_SIZE - 1 , 0, (struct sockaddr *)&servinforead, &addr_len)) == -1)
    {
        perror("talker: recvfrom");
        
        clientStatus = 1;
        return -1;
    }
    
    buffer[numbytes] = '\0';
    
    printf("talker: received %zd bytes\n", numbytes);
//    printf("talker: received %zd bytes, Message: %s\n", numbytes, buffer);
    
	bcopy(buffer, latestMessage, strlen(buffer) + 1);
    
    clientStatus = 1;

    return 1;
}

void shutDownClient()
{
	clientStatus = 0;
    
#ifdef _WIN32
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif
}
