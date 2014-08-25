/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/
#ifndef NOSTL
# include <map>
# include <memory>
#else
# include "autoptr.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

ssize_t TCPConnection::send(const void* msg, size_t len, flag_t flags) {

	char * zsheader = getEgress().c_str();
	if (NULL != zsheader)
	{
		int retval = ::send(this->getFd(),zsheader,strlen(zsheader),0);
		if (retval <= 0)fprintf(stderr,"TCPConnection: Error sending header to destination\n");
		free(zsheader);
	}
	return ::send(this->getFd(),msg, len, flags);
}

/*!
 *
 */
ssize_t TCPConnection::recvhdr (void * buf , size_t len, flag_t flags) {
#ifdef NO_MALLOC
	unsigned char initread [Ingress::maxheader_sz];
#else
	unsigned char * initread;
	initread = new unsigned char [Ingress::maxheader_sz + len];
	if (NULL == initread) return -1;
# ifndef NO_STL
	std::auto_ptr<unsigned char> d_initread (initread);
# else
	zerosocket::auto_ptr<unsigned char> d_initread(initread);
# endif
#endif
	unsigned char * readptr = initread;
	ssize_t totalread_sz = 0;
	bool reread = true;
	size_t maxread = Ingress::maxheader_sz + len; // hope this will be optimized out by compiler, its here for readability
	Ingress::StateHeader_t state;

	//[{123456789012345678901234567890123456789012345678901234567890123456789};2345678901234567890123456789...]
	// ^initread                                                               ^state.second              #read_sz
	do {
		// limit how much we should read
		ssize_t allowread = (maxread-totalread_sz < len)? maxread-totalread_sz : len;
		ssize_t thisread = ::recv(this->getFd(), readptr, allowread, flags);

		state = getIngress().getPayload(initread,totalread_sz);
		switch (state.first)
		{
		case Ingress::HeaderIncomplete: // we would need to read again
			break;
		case Ingress::HeaderComplete:
			// copy the buffer and return, let application read again
			totalread_sz += thisread;
			if (NULL == state.second) return -255; //something very bad happened in JSON processing

			memcpy(buf,state.second,totalread_sz-(state.second-initread));
			return totalread_sz-(state.second-initread);
			break;
		case Ingress::HeaderMissing: // break; as we should have read all possible data from network
			memcpy(buf,initread,thisread);
			return thisread;
		case Ingress::NotReadable: // buf is NULL
			return thisread;
		case Ingress::UNKNOWN:
		default:
			memcpy(buf,initread,thisread); // duplicated, we might need to change the situation in future
			return thisread;
			break;
		}
		if (thisread >= 0){
			totalread_sz += thisread;
			readptr += thisread;
		}
	}while (reread);
	return totalread_sz;
}


ssize_t TCPConnection::recv(void* buf, size_t len, flag_t flags) {
	return recvhdr(buf,len,flags);
}

ssize_t TCPConnection::sendmsg(const struct msghdr* msg, int flags) {
	return -1;
}

ssize_t TCPConnection::recvmsg(struct msghdr* msg, int flags) {
	return -1;
}

/**
 * ignores to and tolen parameters
 * behaves like a TCP send
 */
ssize_t TCPConnection::sendto(const void* msg, size_t len,
		flag_t flags, const struct sockaddr* to, socklen_t tolen) {
	return send(msg, len, flags);
}

ssize_t TCPConnection::recvfrom(void* buf, size_t len, flag_t flags,
		struct sockaddr* from, socklen_t* fromlen) {
	return recv(buf,len,flags);
}

int TCPConnection::close() {
	return ::close(this->getFd());
}

int TCPConnection::shutdown(int how) {
	return ::shutdown(this->getFd(),how);
}

} /* namespace zerosocket */
