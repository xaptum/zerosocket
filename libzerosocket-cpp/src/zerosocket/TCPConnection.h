/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/

#ifndef TCPCONNECTION_H_
#define TCPCONNECTION_H_

#include "Connection.h"

namespace zerosocket {

/*
 *
 */
class TCPConnection: public Connection {
public:
	TCPConnection();
	virtual ~TCPConnection();

	virtual int connect(struct sockaddr *serv_addr, socklen_t addrlen);
	virtual int bind(struct sockaddr *my_addr, socklen_t addrlen);
	virtual int listen(int backlog);
	virtual int accept(struct sockaddr *cliaddr, socklen_t *addrlen);
	virtual int send(const void *msg, size_t len, flag_t flags);
	virtual int recv(void *buf, size_t len, flag_t flags) ;
	virtual int sendto(const void *msg, size_t len, flag_t flags,
			const struct sockaddr *to, socklen_t tolen) ;
	virtual int recvfrom(void *buf, size_t len, flag_t flags,
			struct sockaddr *from, socklen_t *fromlen) ;
	virtual int close();
};

} /* namespace zerosocket */

#endif /* TCPCONNECTION_H_ */
