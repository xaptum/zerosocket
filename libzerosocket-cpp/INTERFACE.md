# ZeroSocket  1.0.0
zerosocket.h File Reference

## Macros

```
#define [SIZEOFARRAY](ARR)   sizeof(ARR)/sizeof(\*ARR)
#define [ZSMAXNAMESZ]   10
#define [ZSMAXVALUSZ]   1536
```

## Enumerations
```
enum [ZSElement] {
    [ZUNK] = 0,
    [ZVER],
    [ZUSR],
    [ZPAS],
    [ZTOK],
    [ZDAT],
    [ZDID],
    [ZMET],
    [ZADR],
    [ZPRT],
    [ZORG],
    [ZDST]
 }
```

##Variables

```
const char const ZSElementName []
const char const ZSElementDesc []
```

##Function Documentation

####enum ZSElement getZSElementIndex (   const char    *name*   )
Get Zero Socket Element Index from name(String) . This function does a
case insensitive string compare to known zero socket keys.

Parameters:

name   as a string

Returns:

appropriate ZSElement when key matches, on error returns ZUNK

***
####const char\* getZSVersion   (   void       )

Returns:
   returns the current library version of protocol supported

***

####<a name="zaccept"/>int zaccept ( int *sockfd*, struct sockaddr \* *cliaddr*, socklen\_t \* *addrlen* )

[zaccept()] call intercepts the accept system call.

[zaccept()] used with connection-based socket types (SOCK\_STREAM, SOCK\_SEQPACKET), It

extracts the first connection request on the queue of pending

connections for the listening socket, sockfd, creates a new connected

socket, and returns a new file descriptor referring to that socket.

Example usage:

```

#include "zerosocket.h"
⋮
int newclient\_sock;
int server\_sock;
struct sockaddr client\_addr;
int addrlen;
//zsocket, zbind, and zlisten have been called
⋮
addrlen = sizeof(client\_addr);
newclient\_sock = [zaccept](server\_sock,&client\_addr, &addrlen);

```

Parameters:

    sockfd    : sockfd is a socket that has been created with zsocket, bound to a local address with zbind, and is listening for connections after a zlisten.

    cliaddr   : cliaddr is a pointer to a sockaddr structure. This structure is filled in with the address of the peer socket, as known to the communications layer.

    addrlen   : addrlen argument is a value-result argument: the caller must initialize it to contain the size (in bytes) of the structure pointed to by addr; on return it will contain the actual size of the peer address.


Returns

    On success, these system calls return a nonnegative integer that is a descriptor for the accepted socket. On error, -1 is returned, and errno is set appropriately.



See Also

    [zsocket](#zsocket)

    [zbind](#zbind)

    [zlisten](#zlisten)

    accept [[man accept](http://man7.org/linux/man-pages/man2/accept.2.html)].

***


####<a name="zbind"/>int zbind ( int *sockfd*, struct sockaddr \* *my\_addr*, int *addrlen* )

zbind() call intercepts the bind system call.

zbind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd. addrlen specifies the size, in bytes, of the address structure pointed to by addr.

Example usage:

```
#include "zerosocket.h"
⋮
int rc;
int s;
struct sockaddr\_in myname;
⋮
// bind to all interfaces
memset(&myname, 0, sizeof(myname));
myname.sin\_family = AF\_INET;
myname.sin\_port = 5001;
myname.sin\_addr.s\_addr = INADDR\_ANY; // all interfaces
rc = zbind (s, (struct sockaddr \*) &myname, sizeof(myname));

```


Parameters
    sockfd   : unassigned socket file descriptor as assigned by zsocket call, do not use return value from socket call to this function

    my\_addr : The actual structure passed for the my\_addr argument will depend on the address family. The sockaddr structure is defined as something like:

```
    struct sockaddr {
    sa\_family\_t sa\_family;
    char sa\_data[14];
    }
```
    
    addrlen  : length of the my\_addr, depends on the address family

Returns
    On success, zero is returned. On error, -1 is returned, and errno is set appropriately.

See Also
   bind [[man bind](http://man7.org/linux/man-pages/man2/bind.2.html)].

Definition at line [186](zerosocket_8cpp_source.html#l00186) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  ------------ --- ------ ---------- --- --
  int zclose   (   int    *sockfd*   )
  ------------ --- ------ ---------- --- --

[zclose()](zerosocket_8cpp.html#acf2f95ec09bae80fd91a1cbc604651cd) call
intercepts the sendto system call.

The [zclose()](zerosocket_8cpp.html#acf2f95ec09bae80fd91a1cbc604651cd)
function shuts down a socket and frees resources allocated to that
socket, including those allocated by zerosocket library. do not call
close as this results in a memory leak.

Example usage:

\#include "[zerosocket.h](zerosocket_8h.html)"

⋮

int rc;

int server\_sock;

⋮

rc =
[zclose](zerosocket_8cpp.html#acf2f95ec09bae80fd91a1cbc604651cd)(server\_sock);

exit(0);

Parameters
:   -------- --------------------------------------------------
      sockfd   file descriptor used generated from zsocket call
      -------- --------------------------------------------------

Returns
:   [zclose()](zerosocket_8cpp.html#acf2f95ec09bae80fd91a1cbc604651cd)
    returns zero on success. On error, -1 is returned, and errno is set
    appropriately.

See Also
:   [zsocket](zerosocket_8h.html#a9a9eb9084c6c207d0518ed80fe27f09c)
:   close
    [[http://man7.org/linux/man-pages/man2/close.2.html](http://man7.org/linux/man-pages/man2/close.2.html)].

Definition at line [454](zerosocket_8cpp_source.html#l00454) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  -------------- --- --------------------- ---------------
  int zconnect   (   int                   *sockfd*,
                     struct sockaddr \*    *serv\_addr*,
                     int                   *addrlen*
                 )
  -------------- --- --------------------- ---------------

zconnect intercepts the 'connect' system call. ipv6 Connect is not yet
supported, to be available shortly. The
[zconnect()](zerosocket_8cpp.html#a44eeef480cd355c827266907afdb4fc1)
call connects the socket referred to by the file descriptor sockfd to
the address specified by addr.

Example usage:

\#include "[zerosocket.h](zerosocket_8h.html)"

⋮

int rc;

int client\_sock;

struct sockaddr\_in server\_addr;

⋮

memset(&server\_addr, 0,sizeof(server\_addr));

server\_addr.sin\_family = AF\_INET;

server\_addr.sin\_port = 5001;

server\_addr.sin\_addr.s\_addr = inet\_addr("129.5.24.1");

rc =
[zconnect](zerosocket_8cpp.html#a44eeef480cd355c827266907afdb4fc1)(client\_sock,
(struct sockaddr \*) &server\_addr,

sizeof(server\_addr));

Parameters
:   ------------ -------------------------------------------------------------------------------------------
      sockfd       the socket descriptor for the connection as returned by zsocket call
      serv\_addr   The format of the address in addr is determined by the address space of the socket sockfd
      addrlen      The addrlen argument specifies the size of addr
      ------------ -------------------------------------------------------------------------------------------

Returns
:   Upon successful completion, a value of 0 is returned. Otherwise, a
    value of -1 is returned and the global integer variable errno is set
    to indicate the error.

See Also
:   [zsocket](zerosocket_8h.html#a9a9eb9084c6c207d0518ed80fe27f09c) for
    further details.
:   connect
    [[http://man7.org/linux/man-pages/man2/connect.2.html](http://man7.org/linux/man-pages/man2/connect.2.html)]
    for details on error return.

Definition at line [142](zerosocket_8cpp_source.html#l00142) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  ------------- --- ------ ------------
  int zlisten   (   int    *sockfd*,
                    int    *backlog*
                )
  ------------- --- ------ ------------

[zlisten()](zerosocket_8cpp.html#a045e7cb5526ac0e8d00d8863621817fe) call
intercepts the listen system call.
[zlisten()](zerosocket_8cpp.html#a045e7cb5526ac0e8d00d8863621817fe)
marks the socket referred to by sockfd as a passive socket, that is, as
a socket that will be used to accept incoming connection requests using
zaccept.

\#include "[zerosocket.h](zerosocket_8h.html)"

⋮

int rc;

int server\_sock;

⋮

rc =
[zlisten](zerosocket_8cpp.html#a045e7cb5526ac0e8d00d8863621817fe)(server\_sock,
5);

Parameters
:   --------- ----------------------------------------------------------------------------------------------------------------
      sockfd    The sockfd argument is a file descriptor that refers to a socket of type SOCK\_STREAM or SOCK\_SEQPACKET.
      backlog   The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow.
      --------- ----------------------------------------------------------------------------------------------------------------

Returns
:   On success, zero is returned. On error, -1 is returned, and errno is
    set appropriately.

See Also
:   [zaccept](zerosocket_8h.html#aef5cff5da6297bf12a7fa164afb270dd)
:   listen
    [[http://man7.org/linux/man-pages/man2/listen.2.html](http://man7.org/linux/man-pages/man2/listen.2.html)].

Definition at line [214](zerosocket_8cpp_source.html#l00214) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  ----------- --- ---------- -----------
  int zrecv   (   int        *sockfd*,
                  void \*    *buf*,
                  size\_t    *len*,
                  int        *flags*
              )
  ----------- --- ---------- -----------

[zrecv()](zerosocket_8cpp.html#a849300c5383b5b33d0797de39af508aa) call
intercepts the recv system call.

[zrecv()](zerosocket_8cpp.html#a849300c5383b5b33d0797de39af508aa) call
may be used only when the socket is in a connected state (so that the
intended recipient is known). the following call

[zrecv](zerosocket_8cpp.html#a849300c5383b5b33d0797de39af508aa)(sockfd,
buf, len, flags);

is equivalent to

[zrecvfrom](zerosocket_8cpp.html#a1e8a479a9444878359f4019b3281b191)(sockfd,
buf, len, flags, NULL, 0);

Example usage:

\#include "[zerosocket.h](zerosocket_8h.html)"

⋮

int rc;

int server\_sock;

char oob\_data;

⋮

rc =
[zrecv](zerosocket_8cpp.html#a849300c5383b5b33d0797de39af508aa)(server\_sock,oob\_data,sizeof(oob\_data),MSG\_OOB);

if (rc \> 0)

{

// Process the oob data from the sender

⋮

}

Parameters
:   -------- -----------------------------------------------------------------------------------------------------------
      sockfd   The sockfd argument is a file descriptor that refers to a socket of type SOCK\_STREAM or SOCK\_SEQPACKET.
      buf      the message is found in buf
      len      length of data to send in buf
      flags    see send manual or follow link below to see possible flags
      -------- -----------------------------------------------------------------------------------------------------------

Returns
:   On success, zero is returned. On error, -1 is returned, and errno is
    set appropriately.

See Also
:   [zrecvfrom](zerosocket_8h.html#a1e8a479a9444878359f4019b3281b191)
:   recv
    [[http://man7.org/linux/man-pages/man2/recv.2.html](http://man7.org/linux/man-pages/man2/recv.2.html)].

Definition at line [333](zerosocket_8cpp_source.html#l00333) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  --------------- --- --------------------- ------------
  int zrecvfrom   (   int                   *sockfd*,
                      void \*               *buf*,
                      size\_t               *len*,
                      int                   *flags*,
                      struct sockaddr \*    *from*,
                      socklen\_t \*         *fromlen*
                  )
  --------------- --- --------------------- ------------

[zrecvfrom()](zerosocket_8cpp.html#a1e8a479a9444878359f4019b3281b191)
call intercepts the recv system call.

[zrecvfrom()](zerosocket_8cpp.html#a1e8a479a9444878359f4019b3281b191)
call may be used when the socket is in any (connected or not) state.

the following call

[zrecv](zerosocket_8cpp.html#a849300c5383b5b33d0797de39af508aa)(sockfd,
buf, len, flags);

is equivalent to

[zrecvfrom](zerosocket_8cpp.html#a1e8a479a9444878359f4019b3281b191)(sockfd,
buf, len, flags, NULL, 0);

Example usage:

int bytes\_recv;

int server\_sock;

char data\_recv[256];

struct sockaddr client\_addr;

socklen\_t addr\_len;

⋮

bytes\_recv =
[zrecvfrom](zerosocket_8cpp.html#a1e8a479a9444878359f4019b3281b191)(server\_sock,
data\_recv, sizeof(data\_recv), 0,

(struct sockaddr \*) &client\_addr, (int \*) &addr\_len);

Parameters
:   --------- ---------------------------------------------------------------------------------------
      sockfd    The sockfd argument is a file descriptor that refers to a socket of type SOCK\_DGRAM.
      buf       the message is found in buf
      len       length of data to send in buf
      flags     see send manual or follow link below to see possible flags
      from      address of sockaddr stored in this location
      fromlen   address of socklen\_t, the length is stored after call
      --------- ---------------------------------------------------------------------------------------

Returns
:   These calls return the number of bytes received, or -1 if an error
    occurred. The return value will be 0 when the peer has performed an
    orderly shutdown.

See Also
:   [zrecv](zerosocket_8h.html#a849300c5383b5b33d0797de39af508aa)
:   recvfrom
    [[http://man7.org/linux/man-pages/man2/recvfrom.2.html](http://man7.org/linux/man-pages/man2/recvfrom.2.html)].

Definition at line [424](zerosocket_8cpp_source.html#l00424) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  ----------- --- ---------------- -----------
  int zsend   (   int              *sockfd*,
                  const void \*    *msg*,
                  int              *len*,
                  int              *flags*
              )
  ----------- --- ---------------- -----------

[zsend()](zerosocket_8cpp.html#a7791b4051d9029da9f48dc94ed29f5d8) call
intercepts the send system call.

[zsend()](zerosocket_8cpp.html#a7791b4051d9029da9f48dc94ed29f5d8) call
may be used only when the socket is in a connected state (so that the
intended recipient is known).

Example Usage:

\#include "[zerosocket.h](zerosocket_8h.html)"

⋮

int bytes\_sent;

int server\_sock;

char data\_sent[256];

⋮

bytes\_sent =
[zsend](zerosocket_8cpp.html#a7791b4051d9029da9f48dc94ed29f5d8)(server\_sock,
data\_sent, sizeof(data\_sent), 0);

Parameters
:   -------- -----------------------------------------------------------------------------------------------------------
      sockfd   The sockfd argument is a file descriptor that refers to a socket of type SOCK\_STREAM or SOCK\_SEQPACKET.
      msg      the message is found in buf
      len      length of data to send in buf
      flags    see send manual or follow link below to see possible flags
      -------- -----------------------------------------------------------------------------------------------------------

Returns
:   On success, zero is returned. On error, -1 is returned, and errno is
    set appropriately.

See Also
:   [zsendto](zerosocket_8h.html#a75f95d40192026cb9a30a2c62ec33f72)
:   send
    [[http://man7.org/linux/man-pages/man2/send.2.html](http://man7.org/linux/man-pages/man2/send.2.html)].

Definition at line [288](zerosocket_8cpp_source.html#l00288) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  ------------- --- --------------------------- -----------
  int zsendto   (   int                         *sockfd*,
                    const void \*               *msg*,
                    int                         *len*,
                    int                         *flags*,
                    const struct sockaddr \*    *to*,
                    socklen\_t                  *tolen*
                )
  ------------- --- --------------------------- -----------

[zsendto()](zerosocket_8cpp.html#a75f95d40192026cb9a30a2c62ec33f72) call
intercepts the sendto system call.

[zsendto()](zerosocket_8cpp.html#a75f95d40192026cb9a30a2c62ec33f72) call
may be used only when the socket is set for Datagram. If
[zsendto()](zerosocket_8cpp.html#a75f95d40192026cb9a30a2c62ec33f72) is
used on a connection-mode (SOCK\_STREAM, SOCK\_SEQPACKET) socket, the
arguments dest\_addr and addrlen are ignored the following call

[zsend](zerosocket_8cpp.html#a7791b4051d9029da9f48dc94ed29f5d8)(sockfd,
buf, len, flags);

is equivalent to

[zsendto](zerosocket_8cpp.html#a75f95d40192026cb9a30a2c62ec33f72)(sockfd,
buf, len, flags, NULL, 0);

Example usage:

int bytes\_sent;

int server\_sock;

char send\_msg[100];

struct sockaddr\_in to\_addr;

⋮

to\_addr.sin\_family = AF\_INET;

to\_addr.sin\_port = 5001;

to\_addr.sin\_addr.s\_addr = inet\_addr("129.5.24.1");

bytes\_sent =
[zsendto](zerosocket_8cpp.html#a75f95d40192026cb9a30a2c62ec33f72)(server\_sock,
send\_msg, sizeof(send\_msg), 0,

(struct sockaddr \*)&to\_addr, sizeof(to\_addr));

Parameters
:   -------- ------------------------------------------------------------------
      sockfd   The sockfd argument is a file descriptor that refers to a socket
      msg      the message is found in buf
      len      length of data to send in buf
      flags    see send manual or follow link below to see possible flags
      to       the address of the target is given by to
      tolen    specifying the size of to structure.
      -------- ------------------------------------------------------------------

Returns
:   On success, zero is returned. On error, -1 is returned, and errno is
    set appropriately.

See Also
:   [zsend](zerosocket_8h.html#a7791b4051d9029da9f48dc94ed29f5d8)
:   sendto
    [[http://man7.org/linux/man-pages/man2/sendto.2.html](http://man7.org/linux/man-pages/man2/sendto.2.html)].

Definition at line [379](zerosocket_8cpp_source.html#l00379) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

  ------------- --- ------ -------------
  int zsocket   (   int    *family*,
                    int    *type*,
                    int    *protocol*
                )
  ------------- --- ------ -------------

[zsocket()](zerosocket_8cpp.html#a9a9eb9084c6c207d0518ed80fe27f09c) call
creates an interceptor for the socket system call. Currently supported
implementation is for TCP(Stream) and UDP(Datagram)

Example usage:

\#include "[zerosocket.h](zerosocket_8h.html)"

⋮

int server\_sock;

⋮

server\_sock =
[zsocket](zerosocket_8cpp.html#a9a9eb9084c6c207d0518ed80fe27f09c)(AF\_INET,
SOCK\_STREAM, 0);

Parameters
:   ---------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      family     The family parameter specifies a communications domain within which communication will take place; this selects the protocol family which should be used. These families are defined in the include file \<sys/socket.h\>. The currently understood formats are PF\_INET Internet version 4 protocols, PF\_INET6 Internet version 6 protocols
      type       The socket has the indicated type, which specifies the semantics of communication. Currently defined types are: SOCK\_STREAM SOCK\_DGRAM SOCK\_RAW SOCK\_SEQPACKET SOCK\_RDM
      protocol   The protocol specifies a particular protocol to be used with the socket. Normally only a single protocol exists to support a particular socket type within a given protocol family. However, it is possible that many protocols may exist, in which case a particular protocol must be specified in this manner. The protocol number to use is particular to the communication domain in which communication is to take place;
      ---------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Returns
:   returns the socket descriptor for the newly created socket

See Also
:   protocols
    [[http://man7.org/linux/man-pages/man5/protocols.5.html](http://man7.org/linux/man-pages/man5/protocols.5.html)].
:   socket
    [[http://man7.org/linux/man-pages/man2/socket.2.html](http://man7.org/linux/man-pages/man2/socket.2.html)]
    for error return values

Definition at line [106](zerosocket_8cpp_source.html#l00106) of file
[zerosocket.cpp](zerosocket_8cpp_source.html).

Variable Documentation
----------------------

  ------------------------------------
  const char\* const ZSElementDesc[]
  ------------------------------------

**Initial value:**

{

"UNKNOWN",

"ProtocolVersion",

"Username",

"Password",

"Token",

"Date",

"DeviceId",

"Method",

"Address",

"Port",

"Origin",

"Destination"

}

Definition at line [45](zerosocket_8h_source.html#l00045) of file
[zerosocket.h](zerosocket_8h_source.html).

  ------------------------------------
  const char\* const ZSElementName[]
  ------------------------------------

**Initial value:**

{ "UNKN", "zver", "zusr", "zpas", "ztok",

"zdat", "zdid", "zmet", "zadr", "zprt" , "zorg" , "zdst" }

Definition at line [42](zerosocket_8h_source.html#l00042) of file
[zerosocket.h](zerosocket_8h_source.html).

* * * * *

Generated on Tue Aug 19 2014 23:13:37 for ZeroSocket by
 [![doxygen](doxygen.png)](http://www.doxygen.org/index.html) 1.8.1.2