/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/
#ifndef NOSTL
# include <map>
#endif
#include "Egress.h"
#include "Ingress.h"
#include "Config.h"
#include "Descriptor.h"
#include "ConnectionStore.h"


#ifndef CONNECTION_H_
#define CONNECTION_H_

namespace zerosocket {

/*
 * The Connection class, use static members in class to create stream or datagram sockets
 *  and return corresponding (TCP/UDP)
 * You'll not be able to create a blank Connection Object as it is abstract
 */

class Connection : public Descriptor{
public: // Static methods for singleton and Tree lookup
	static Connection* getConnection(int sockfd);
	static int newConnection(int family, int type, int protocol);
	static Config* getConfig() {return _config;}
	static void setConfig(Config* config) {_config = config;}

private:
	static ConnectionStore store;
	static Config * _config;
	static int newIPv4Connection(int type, int protocol);
	static int newIPv6Connection(int type, int protocol);

private:
	int fd;
	Egress egress;
	Ingress ingress;
protected:
	virtual int key() const {return fd;};
	virtual void print() const;
	virtual void setFd(int fd) {this->fd = fd;}
public:
	typedef int flag_t;
	Connection();
	virtual ~Connection();
	virtual int getFd() const {return fd;}

	virtual int connect(struct sockaddr *serv_addr, socklen_t addrlen) = 0;
	virtual int bind(struct sockaddr *my_addr,socklen_t addrlen) = 0;
	virtual int listen(int backlog) = 0;
	virtual int accept (struct sockaddr *cliaddr, socklen_t *addrlen) = 0;
	virtual int send(const void *msg, size_t len, flag_t flags) = 0;
	virtual int recv(void *buf, size_t len, flag_t flags) = 0;
	virtual int sendto(const void *msg, size_t len, flag_t flags,
			const struct sockaddr *to, socklen_t tolen) = 0;
	virtual int recvfrom(void *buf, size_t len, flag_t flags,
			struct sockaddr *from, socklen_t *fromlen) = 0;
	virtual int close() = 0;
	const Egress& getEgress() const;
	const Ingress& getIngress() const;
};

} /* namespace zerosocket */

#endif /* CONNECTION_H_ */
