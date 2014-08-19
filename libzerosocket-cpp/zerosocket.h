/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/
#include <sys/types.h>
#include <sys/socket.h>

#ifndef ZEROSOCKET_H_
#define ZEROSOCKET_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum ZSElement {
	ZUNK = 0,
	ZVER, // 1
	ZUSR, // 2
	ZPAS, // 3
	ZTOK, // 4
	ZDAT, // 5
	ZDID, // 6
	ZMET, // 7
	ZADR, // 8
	ZPRT, // 9
	ZORG, // 10
	ZDST  // 11
};

const char * const ZSElementName [] = { "UNKN", "zver", "zusr", "zpas", "ztok",
		"zdat", "zdid", "zmet", "zadr", "zprt" , "zorg" , "zdst" };

const char * const ZSElementDesc [] = {
		"UNKNOWN",
		"ProtocolVersion",
		"Username",
		"Password",
		"Token",
		"Date",
		"DeviceId",
		"Method",
		"Address",
		"Port",
		"Origin",
		"Destination"
	};

#define SIZEOFARRAY(ARR) sizeof(ARR)/sizeof(*ARR)
#define ZSMAXNAMESZ 10

enum ZSElement getZSElementIndex(const char * name) ;

const char * getZSVersion(void);

/**
 * patched system calls
 */

int zsocket (int family, int type, int protocol);
int zconnect(int sockfd, struct sockaddr *serv_addr, int addrlen);
int zbind(int sockfd, struct sockaddr *my_addr,int addrlen);
int zlisten(int sockfd,int backlog);
int zaccept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
int zsend(int sockfd, const void *msg, int len, int flags);
int zrecv(int sockfd, void *buf, int len, int flags);
int zsendto(int sockfd, const void *msg, size_t len, int flags,
		   const struct sockaddr *to, socklen_t tolen);
int zrecvfrom(int sockfd, void *buf, size_t len, int flags,
		     struct sockaddr *from, socklen_t *fromlen);
int zclose( int sockfd );

#ifdef __cplusplus
}
#endif

#endif /* ZEROSOCKET_H_ */
