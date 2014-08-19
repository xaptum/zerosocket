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
#include <sys/socket.h>
#include "TCPConnection.h"

namespace zerosocket {

TCPConnection::TCPConnection()
:Connection()
{
	int sd = socket(AF_INET,SOCK_STREAM,0);
	this->setFd(sd);
}

TCPConnection::~TCPConnection() {
	this->close();
}

int TCPConnection::connect(struct sockaddr* serv_addr,
		socklen_t addrlen) {
	return ::connect(this->getFd(),serv_addr,addrlen);
}

int TCPConnection::bind(struct sockaddr* my_addr, socklen_t addrlen) {
	return ::bind(this->getFd(),my_addr,addrlen);
}

int TCPConnection::listen(int backlog) {
	return ::listen(this->getFd(),backlog);
}

int TCPConnection::accept(struct sockaddr* cliaddr,
		socklen_t* addrlen) {
	return ::accept(this->getFd(),cliaddr,addrlen);
}

int TCPConnection::send(const void* msg, size_t len, flag_t flags) {
	return ::send(this->getFd(),msg, len, flags);
}

int TCPConnection::recv(void* buf, size_t len, flag_t flags) {
	return ::recv(this->getFd(), buf, len, flags);
}

/**
 * ignores to and tolen parameters
 * behaves like a TCP send
 */
int TCPConnection::sendto(const void* msg, size_t len,
		flag_t flags, const struct sockaddr* to, socklen_t tolen) {
	return send(msg, len, flags);
}

int TCPConnection::recvfrom(void* buf, size_t len, flag_t flags,
		struct sockaddr* from, socklen_t* fromlen) {
	return recv(buf,len,flags);
}

int TCPConnection::close() {
	return ::close(this->getFd());
}

} /* namespace zerosocket */
