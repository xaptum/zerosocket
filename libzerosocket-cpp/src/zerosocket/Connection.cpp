/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "Connection.h"

namespace zerosocket {

Connection::Connection()
	:fd(0)
{
	// TODO Auto-generated constructor stub

}

Connection* Connection::getConnection(int sockfd) {
	//if (Connection::hashmap)
}

int Connection::newConnection(int family, int type, int protocol) {
	switch(family)
	{
	case AF_INET:
		return Connection::newIPv4Connection(type,protocol);
		break;
	case AF_INET6:
		return Connection::newIPv6Connection(type,protocol);
		break;
	case AF_LOCAL:
	case AF_ROUTE:
	default:
		return -1;
		break;
	}
	return -1;
}

/**
 *
 */
int Connection::newIPv4Connection(int type, int protocol) {
	Connection * conn = NULL;
	switch (type)
	{
	case SOCK_STREAM: //Stream socket , TCP
	{
		//conn = new TCPConnection();
	}break;
	case SOCK_DGRAM: //Datagram socket
	{
		//conn = new UDPConnection();
	}break;
	case SOCK_SEQPACKET: //Sequenced packet socket
	case SOCK_RAW: //
	default:
		return -1;
		break;
	}
	// add to map
	if (conn && conn > 0){
		hashmap[conn->getFd()] = conn;
		return conn->getFd();
	}else return -1;
}

int Connection::newIPv6Connection(int type, int protocol) {
	Connection * conn = NULL;
	switch (type)
	{
	case SOCK_STREAM: //Stream socket , TCP
	{
		//conn = new TCPConnection();
	}break;
	case SOCK_DGRAM: //Datagram socket
	{
		//conn = new UDPConnection();
	}break;
	case SOCK_SEQPACKET: //Sequenced packet socket
	case SOCK_RAW: //
	default:
		return -1;
		break;
	}
	// add to map
	if (conn && conn > 0){
		hashmap[conn->getFd()] = conn;
		return conn->getFd();
	}else return -1;
}

void Connection::print() const {
}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

} /* namespace zerosocket */
