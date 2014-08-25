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
#include <unistd.h>
#include <string.h>
#include "UDPConnection.h"

namespace zerosocket {

UDPConnection::UDPConnection() {
	int sd = socket(AF_INET,SOCK_DGRAM,0);
	this->setFd(sd);
}

UDPConnection::~UDPConnection() {
	this->close();
}

/**
 * connect not implemented for UDP
 */
int UDPConnection::connect(struct sockaddr* serv_addr,
		socklen_t addrlen) {
	return -1;
}

int UDPConnection::bind(struct sockaddr* my_addr, socklen_t addrlen) {
	return ::bind(this->getFd(),my_addr,addrlen);
}

/**
 * listen not implemented for UDP
 */
int UDPConnection::listen(int backlog) {
	return -1;
}

/**
 * accept not implemented for UDP
 */
int UDPConnection::accept(struct sockaddr* cliaddr,
		socklen_t* addrlen) {
	return -1;
}

/**
 * send not implemented for UDP
 */
ssize_t UDPConnection::send(const void* msg, size_t len, flag_t flags) {
	return -1;
}

/**
 * recv not implemented for UDP
 */
ssize_t UDPConnection::recv(void* buf, size_t len, flag_t flags) {
	return -1;
}

/**
 * true UDP send
 */
ssize_t UDPConnection::sendto(const void* msg, size_t len,
		flag_t flags, const struct sockaddr* to, socklen_t tolen) {
	Egress egress = this->getEgress();
	char * zsheader = egress.c_str();
	if (NULL != zsheader)
	{
		int retval = ::sendto(this->getFd(),zsheader,strlen(zsheader),0, to, tolen);
		if (retval <= 0)fprintf(stderr,"UDPConnection: Error sending header to destination\n");
		free(zsheader);
	}
	return ::sendto(this->getFd(), msg, len, flags, to, tolen);
}

ssize_t UDPConnection::recvfrom(void* buf, size_t len, flag_t flags,
		struct sockaddr* from, socklen_t * fromlen) {

	return ::recvfrom(this->getFd(), buf, len, flags, from, fromlen);
}

int UDPConnection::close() {
	return ::close(this->getFd());
}

ssize_t UDPConnection::sendmsg(const struct msghdr* msg, int flags) {
	return -1;
}

ssize_t UDPConnection::recvmsg(struct msghdr* msg, int flags) {
	return -1;
}

int UDPConnection::shutdown(int how) {
	return ::shutdown(this->getFd(),how);
}

} /* namespace zerosocket */

