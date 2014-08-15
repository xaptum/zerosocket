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
#endif

#ifndef CONNECTION_H_
#define CONNECTION_H_

namespace zerosocket {

/*
 *
 */

class RBNode;
class RBTree;
class Connection {
	friend class RBNode;
	friend class RBTree;
	typedef std::map <int,Connection*> ConnectionMap_t;
public: // Static methods for singleton and Tree lookup
#ifndef NOSTL
	static ConnectionMap_t hashmap;
#else
	static RBTree hashmap;
#endif
	static Connection* getConnection(int sockfd);
	static int newConnection(int family, int type, int protocol);
private:
	static int newIPv4Connection(int type, int protocol);
	static int newIPv6Connection(int type, int protocol);

private:
	int fd;
protected:
	virtual int key() const {return fd;};
	virtual void print() const;
	void setFd(int fd) {this->fd = fd;}
public:
	Connection();
	virtual ~Connection();
	int getFd() const {return fd;}

	virtual int connect(struct sockaddr *serv_addr, int addrlen) = 0;
	virtual int bind(struct sockaddr *my_addr,int addrlen) = 0;
	virtual int listen(int backlog) = 0;
	virtual int accept (struct sockaddr *cliaddr, socklen_t *addrlen) = 0;
	virtual int send(const void *msg, int len, int flags) = 0;
	virtual int recv(void *buf, int len, unsigned int flags) = 0;
	virtual int sendto(const void *msg, int len, unsigned int flags,
			   const struct sockaddr *to, socklen_t tolen) = 0;
	virtual int recvfrom(void *buf, int len, unsigned int flags,
			     struct sockaddr *from, socklen_t *fromlen) = 0;
	virtual int _close() = 0;

};

} /* namespace zerosocket */

#endif /* CONNECTION_H_ */
