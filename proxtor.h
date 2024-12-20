#ifndef PROXTOR_H
#define PROXTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <dlfcn.h>

#define PROXYHOST "127.0.0.1"
#define PROXYPORT 9050
#define reqsize sizeof(proxy_request)
#define ressize sizeof(proxy_response)
#define USERNAME "xaixane"
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

typedef struct request{
	int8 vn;
	int8 cd;
	int16 dstport;
	int32 dstip;
	char userid[8];
}proxy_request;

typedef struct response{
	int8 vn;
	int8 cd;
	int16 dstport;
	int32 dstip;
}proxy_response;

proxy_request * make_request(struct sockaddr_in*);

int connect(int, const struct sockaddr *,socklen_t);

#endif
