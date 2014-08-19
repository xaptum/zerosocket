/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/
#include <ctype.h>
#include <string.h>
#include "version.h"
#include "zerosocket.h"
#include "Connection.h"

using namespace zerosocket;
const char * zerosocket::_version = "1.0";

enum ZSElement
getZSElementIndex(const char * name)
{
	char iname[ZSMAXNAMESZ];
	size_t i,n;
	n = ZSMAXNAMESZ;
	for (i = 0; i < n && name[i] != '\0'; i++)
		iname[i] = tolower(name[i]);
	for ( ; i < n; i++)
		iname[i] = '\0';

	if ( strcmp(iname, ZSElementName[ZUSR]) == 0)
		return ZUSR;
	else if ( strcmp(iname, ZSElementName[ZPAS]) == 0)
		return ZPAS;
	else if ( strcmp(iname, ZSElementName[ZTOK]) == 0)
		return ZTOK;
	else if ( strcmp(iname, ZSElementName[ZDAT]) == 0)
		return ZDAT;
	else if ( strcmp(iname, ZSElementName[ZDID]) == 0)
		return ZDID;
	else if ( strcmp(iname, ZSElementName[ZMET]) == 0)
		return ZMET;
	else if ( strcmp(iname, ZSElementName[ZADR]) == 0)
		return ZADR;
	else if ( strcmp(iname, ZSElementName[ZPRT]) == 0)
		return ZPRT;
	else if ( strcmp(iname, ZSElementName[ZORG]) == 0)
		return ZORG;
	else if ( strcmp(iname, ZSElementName[ZDST]) == 0)
		return ZDST;
	else
		return ZUNK;
}

const char *
getZSVersion(void)
{
	return _version;
}

/**
 * patched system calls
 */

int zsocket (int family, int type, int protocol)
{
	return Connection::newConnection(family,type,protocol);
}

int zconnect(int sockfd, struct sockaddr *serv_addr, int addrlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->connect(serv_addr,addrlen);
}

int zbind(int sockfd, struct sockaddr *my_addr,int addrlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->bind(my_addr,addrlen);
}

int zlisten(int sockfd,int backlog)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->listen(backlog);
}

int zaccept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->accept(cliaddr,addrlen);
}

int zsend(int sockfd, const void *msg, int len, int flags)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->send(msg,len,flags);
}

int zrecv(int sockfd, void *buf, size_t len, int flags)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->recv(buf,len,flags);
}

int zsendto(int sockfd, const void *msg, int len, int flags,
		   const struct sockaddr *to, socklen_t tolen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->sendto(msg,len,flags,to,tolen);
}

int zrecvfrom(int sockfd, void *buf, size_t len, int flags,
		     struct sockaddr *from, socklen_t *fromlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->recvfrom(buf,len,flags,from,fromlen);
}

int zclose( int sockfd )
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	int retval = conn->close();
	delete conn;
	return retval;
}
