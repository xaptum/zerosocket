/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "Config.h"
#include "Connection.h"
#include "TCPConnection.h"
#include "UDPConnection.h"

namespace zerosocket {


Connection::Connection()
	:fd(-1),egress(Connection::getConfig()), ingress(Connection::getConfig())
{
}

/**
 * Translate the sockfd to connection ID
 */
Connection* Connection::getConnection(int sockfd) {
	return dynamic_cast<Connection*>(Connection::store.get(sockfd));
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
		conn = dynamic_cast<Connection *>(new zerosocket::TCPConnection());
		break;
	case SOCK_DGRAM: //Datagram socket
		conn = dynamic_cast<Connection *>(new zerosocket::UDPConnection());
		break;
	case SOCK_SEQPACKET: //Sequenced packet socket
	case SOCK_RAW: //
	default:
		return -1;
		break;
	}
	// add to map
	if (conn && conn > 0){
		store.set(conn->getFd(),conn);
		return conn->getFd();
	}else return -1;
}

int Connection::newIPv6Connection(int type, int protocol) {
	Connection * conn = NULL;
	switch (type)
	{
	case SOCK_STREAM: //Stream socket , TCP
		conn = dynamic_cast<Connection *>(new TCPConnection());
		break;
	case SOCK_DGRAM: //Datagram socket
		conn = dynamic_cast<Connection *>(new UDPConnection());
		break;
	case SOCK_SEQPACKET: //Sequenced packet socket
	case SOCK_RAW: //
	default:
		return -1;
		break;
	}
	// add to map
	if (conn && conn > 0){
		store.set(conn->getFd(),conn);
		return conn->getFd();
	}else return -1;
}

void Connection::print() const {
}

Connection::~Connection() {
}

const Egress& Connection::getEgress() const {
	return egress;
}

const Ingress& Connection::getIngress() const {
	return ingress;
}

} /* namespace zerosocket */

