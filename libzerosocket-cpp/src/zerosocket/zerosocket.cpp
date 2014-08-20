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

/*!
 * Get Zero Socket Element Index from name(String) . This function does a case
 * insensitive string compare to known zero socket keys.
 *@param name as a string (char *)
 *@return appropriate ZSElement when key matches, on error returns ZUNK
 *@see ZSElement
 */
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

/*!
 *@return returns the current library version of protocol supported
 */
const char *
getZSVersion(void)
{
	return _version;
}

// ------------- patched system calls --------------

/*!
 * zsocket() call creates an interceptor for the socket system call.
 * Currently supported implementation is for TCP(Stream) and UDP(Datagram)
 *
 * Example usage:
 * @code
 * #include "zerosocket.h"
 * ⋮
 * int server_sock;
 * ⋮
 * server_sock = zsocket(AF_INET, SOCK_STREAM, 0);
 * @endcode
 *@param family The family parameter specifies a communications domain within which
 *	communication will take place; this selects the protocol family which should be used.
 *	These families are defined in the include file <sys/socket.h>.  The currently
 *	understood formats are
 *         PF_INET         Internet version 4 protocols,
 *         PF_INET6        Internet version 6 protocols
 *@param type The socket has the indicated type, which specifies the semantics of
 *	communication. Currently defined types are:
 *         SOCK_STREAM
 *         SOCK_DGRAM
 *         SOCK_RAW
 *         SOCK_SEQPACKET
 *         SOCK_RDM
 *@param protocol The protocol specifies a particular protocol to be used with the socket.
 *	Normally only a single protocol exists to support a particular socket type within
 *	a given protocol family.  However, it is possible that many protocols may exist,
 *	in which case a particular protocol must be specified in this manner. The protocol
 *	number to use is particular to the communication domain in which communication
 *	is to take place;
 *@return returns the socket descriptor for the newly created socket
 *@see protocols [http://man7.org/linux/man-pages/man5/protocols.5.html].
 *@see socket [http://man7.org/linux/man-pages/man2/socket.2.html] for error return values
 */
int zsocket (int family, int type, int protocol)
{
	return Connection::newConnection(family,type,protocol);
}

/*!
 * zconnect intercepts the 'connect' system call.
 * ipv6 Connect is not yet supported, to be available shortly.
 * The zconnect() call connects the socket referred to by the file descriptor sockfd
 * 	to the address specified by addr.
 *
 * Example usage:
 * @code{.C}
 * #include "zerosocket.h"
 * ⋮
 * int rc;
 * int client_sock;
 * struct sockaddr_in server_addr;
 * ⋮
 * memset(&server_addr, 0,sizeof(server_addr));
 * server_addr.sin_family      = AF_INET;
 * server_addr.sin_port        = 5001;
 * server_addr.sin_addr.s_addr = inet_addr("129.5.24.1");
 * rc = zconnect(client_sock, (struct sockaddr *) &server_addr,
 *              sizeof(server_addr));
 * @endcode
 * @param sockfd the socket descriptor for the connection as returned by zsocket call
 * @param serv_addr The format of the address in addr is determined by the address
 * 	space of the socket sockfd
 * @param addrlen The addrlen argument specifies the size of addr
 * @return Upon successful completion, a value of 0 is returned.  Otherwise, a value
 * 	of -1 is returned and the global integer variable errno is set to indicate the error.
 * @see zsocket for further details.
 * @see connect [http://man7.org/linux/man-pages/man2/connect.2.html] for details
 * 	on error return.
 */
int zconnect(int sockfd, struct sockaddr *serv_addr, int addrlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->connect(serv_addr,addrlen);
}

/*!
 * zbind() call intercepts the bind system call.
 * zbind() assigns the address specified by addr to the socket referred to by the
 * 	file descriptor sockfd. addrlen specifies the size, in bytes, of the address
 * 	structure pointed to by addr.
 *
 * 	Example usage:
 * @code
 * #include "zerosocket.h"
 * ⋮
 * int rc;
 * int s;
 * struct sockaddr_in myname;
 * ⋮
 * // bind to all interfaces
 * memset(&myname, 0, sizeof(myname));
 * myname.sin_family      = AF_INET;
 * myname.sin_port        = 5001;
 * myname.sin_addr.s_addr = INADDR_ANY; // all interfaces
 * rc = zbind(s, (struct sockaddr *) &myname, sizeof(myname));
 * @endcode
 *
 * @param sockfd unassigned socket file descriptor as assigned by zsocket call,
 * 	do not use  return value from socket call to this function
 * @param my_addr The actual structure passed for the my_addr argument will depend
 * 	on the address family.  The sockaddr structure is defined as something like:
 * @code{.c}
 *          struct sockaddr {
 *               sa_family_t sa_family;
 *               char        sa_data[14];
 *          }
 * @endcode
 * @param addrlen length of the my_addr, depends on the address family
 * @return On success, zero is returned. On error, -1 is returned, and errno is
 * 	set appropriately.
 * @see bind [http://man7.org/linux/man-pages/man2/bind.2.html].
 */
int zbind(int sockfd, struct sockaddr *my_addr,int addrlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->bind(my_addr,addrlen);
}

/*!
 * zlisten() call intercepts the listen system call.
 * zlisten() marks the socket referred to by sockfd as a passive socket, that is,
 *  as a socket that will be used to accept incoming connection requests using zaccept.
 * @code
 * #include "zerosocket.h"
 * ⋮
 * int rc;
 * int server_sock;
 * ⋮
 * rc = zlisten(server_sock, 5);
 * @endcode
 * @param sockfd The sockfd argument is a file descriptor that refers to a socket
 * 	of type SOCK_STREAM or SOCK_SEQPACKET.
 * @param backlog The backlog argument defines the maximum length to which the
 *  queue of pending connections for sockfd may grow.
 * @return On success, zero is returned. On error, -1 is returned, and errno is
 *  set appropriately.
 * @see zaccept
 * @see listen [http://man7.org/linux/man-pages/man2/listen.2.html].
 */
int zlisten(int sockfd,int backlog)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->listen(backlog);
}

/*!
 * zaccept() call intercepts the accept system call.
 * zaccept() used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET),
 * 	It extracts the first connection request on the queue of pending connections
 * 	for the listening socket, sockfd, creates a new connected socket, and returns
 * 	a new file descriptor referring to that socket.
 *
 * Example usage:
 * @code
 * #include "zerosocket.h"
 * ⋮
 * int newclient_sock;
 * int server_sock;
 * struct sockaddr client_addr;
 * int addrlen;
 * //zsocket, zbind, and zlisten have been called
 * ⋮
 * addrlen = sizeof(client_addr);
 * newclient_sock = zaccept(server_sock, &client_addr, &addrlen);
 * @endcode
 * @param sockfd sockfd is a socket that has been created with zsocket, bound to a
 * 	local address with zbind, and is listening for connections after a zlisten.
 * @param cliaddr cliaddr  is  a  pointer  to  a sockaddr structure.  This structure
 * 	is filled in with the address of the peer socket, as known to the communications layer.
 * @param addrlen addrlen argument is a value-result argument: the caller must initialize
 * 	it to contain the size (in bytes) of the structure pointed to by addr; on return
 * 	it will contain the actual size of the peer address.
 * @return On success, these system calls return a nonnegative integer that is a descriptor
 * 	for the accepted socket.  On error, -1 is returned, and errno is set appropriately.
 * @see zsocket
 * @see zbind
 * @see zlisten
 * @see accept [http://man7.org/linux/man-pages/man2/accept.2.html].
 */
int zaccept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->accept(cliaddr,addrlen);
}

/*!
 * zsend() call intercepts the send system call.
 *
 * zsend() call may be used only when the socket is in a connected state
 * 	(so that the intended recipient is known).
 *
 * Example Usage:
 * @code
 * #include "zerosocket.h"
 * ⋮
 * int bytes_sent;
 * int server_sock;
 * char data_sent[256];
 * ⋮
 * bytes_sent = zsend(server_sock, data_sent, sizeof(data_sent), 0);
 * @endcode
 * @param sockfd The sockfd argument is a file descriptor that refers to a socket
 * 	of type SOCK_STREAM or SOCK_SEQPACKET.
 * @param msg the message is found in buf
 * @param len length of data to send in buf
 * @param flags see send manual or follow link below to see possible flags
 * @return On success, zero is returned. On error, -1 is returned, and errno is
 *  set appropriately.
 * @see zsendto
 * @see send [http://man7.org/linux/man-pages/man2/send.2.html].
 */
int zsend(int sockfd, const void *msg, int len, int flags)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->send(msg,len,flags);
}

/*!
 * zrecv() call intercepts the recv system call.
 *
 * zrecv() call may be used only when the socket is in a connected state
 * 	(so that the intended recipient is known). the following call
 * @code
 *	   zrecv(sockfd, buf, len, flags);
 * @endcode
 * is equivalent to
 * @code
 *     zrecvfrom(sockfd, buf, len, flags, NULL, 0);
 * @endcode
 *
 * Example usage:
 * @code
 * #include "zerosocket.h"
 * ⋮
 * int  rc;
 * int  server_sock;
 * char oob_data;
 * ⋮
 * rc = zrecv(server_sock,oob_data,sizeof(oob_data),MSG_OOB);
 * if (rc > 0)
 * {
 * //  Process the oob data from the sender
 * ⋮
 * }
 * @endcode
 * @param sockfd The sockfd argument is a file descriptor that refers to a socket
 * 	of type SOCK_STREAM or SOCK_SEQPACKET.
 * @param buf the message is found in buf
 * @param len length of data to send in buf
 * @param flags see send manual or follow link below to see possible flags
 * @return On success, zero is returned. On error, -1 is returned, and errno is
 *  set appropriately.
 * @see zrecvfrom
 * @see recv [http://man7.org/linux/man-pages/man2/recv.2.html].
 */
int zrecv(int sockfd, void *buf, size_t len, int flags)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->recv(buf,len,flags);
}

/*!
 * zsendto() call intercepts the sendto system call.
 *
 * zsendto() call may be used only when the socket is set for Datagram.
 * If zsendto() is used on a connection-mode (SOCK_STREAM, SOCK_SEQPACKET) socket,
 * the arguments dest_addr and addrlen are ignored
 *  the following call
 * @code
 *	   zsend(sockfd, buf, len, flags);
 * @endcode
 * is equivalent to
 * @code
 *     zsendto(sockfd, buf, len, flags, NULL, 0);
 * @endcode
 * Example usage:
 * @code{.C}
 * 		int    bytes_sent;
 * 		int    server_sock;
 * 		char   send_msg[100];
 * 		struct sockaddr_in to_addr;
 * 		⋮
 * 		to_addr.sin_family      = AF_INET;
 * 		to_addr.sin_port        = 5001;
 * 		to_addr.sin_addr.s_addr = inet_addr("129.5.24.1");
 * 		bytes_sent = zsendto(server_sock, send_msg, sizeof(send_msg), 0,
 *      	               (struct sockaddr *)&to_addr, sizeof(to_addr));
 * @endcode
 * @param sockfd The sockfd argument is a file descriptor that refers to a socket
 * @param msg the message is found in buf
 * @param len length of data to send in buf
 * @param flags see send manual or follow link below to see possible flags
 * @param to the address of the target is given by to
 * @param tolen specifying the size of to structure.
 * @return On success, zero is returned. On error, -1 is returned, and errno is
 *  set appropriately.

 * @see zsend
 * @see sendto [http://man7.org/linux/man-pages/man2/sendto.2.html].
 */
int zsendto(int sockfd, const void *msg, int len, int flags,
		   const struct sockaddr *to, socklen_t tolen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->sendto(msg,len,flags,to,tolen);
}

/*!
 * zrecvfrom() call intercepts the recv system call.
 *
 * zrecvfrom() call may be used when the socket is in any (connected or not) state.
 *
 * the following call
 * @code
 *	   zrecv(sockfd, buf, len, flags);
 * @endcode
 * is equivalent to
 * @code
 *     zrecvfrom(sockfd, buf, len, flags, NULL, 0);
 * @endcode
 *
 * Example usage:
 * @code
 * int bytes_recv;
 * int server_sock;
 * char data_recv[256];
 * struct sockaddr client_addr;
 * socklen_t addr_len;
 * ⋮
 * bytes_recv = zrecvfrom(server_sock, data_recv, sizeof(data_recv), 0,
 *                     (struct sockaddr *) &client_addr, (int *) &addr_len);
 * @endcode
 * @param sockfd The sockfd argument is a file descriptor that refers to a socket
 * 	of type SOCK_DGRAM.
 * @param buf the message is found in buf
 * @param len length of data to send in buf
 * @param flags see send manual or follow link below to see possible flags
 * @param from address of sockaddr stored in this location
 * @param fromlen address of socklen_t, the length is stored after call
 * @return These calls return the number of bytes received, or -1 if an error occurred.
 *  The return value will be 0 when the peer has performed an orderly shutdown.
 * @see zrecv
 * @see recvfrom [http://man7.org/linux/man-pages/man2/recvfrom.2.html].
 */
int zrecvfrom(int sockfd, void *buf, size_t len, int flags,
		     struct sockaddr *from, socklen_t *fromlen)
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	return conn->recvfrom(buf,len,flags,from,fromlen);
}

/*!
 * zclose() call intercepts the sendto system call.
 *
 * The zclose() function shuts down a socket and frees resources allocated to that socket,
 * including those allocated by zerosocket library. do not call close as this results
 * in a memory leak.
 *
 * Example usage:
 * @code
 * #include "zerosocket.h"
 * ⋮
 * int rc;
 * int server_sock;
 * ⋮
 * rc = zclose(server_sock);
 * exit(0);
 * @endcode
 * @param sockfd file descriptor used generated from zsocket call
 * @return zclose() returns zero on success.  On error, -1 is returned, and errno is set appropriately.
 * @see zsocket
 * @see close [http://man7.org/linux/man-pages/man2/close.2.html].
 */
int zclose( int sockfd )
{
	Connection* conn = Connection::getConnection(sockfd);
	if (! conn) return -1;
	int retval = conn->close();
	delete conn;
	return retval;
}
