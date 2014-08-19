/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/
#include "Descriptor.h"
#ifndef MAXCONNECTION_SZ
# ifndef NOSTL
#  include <map>
# else
#  include "RBTree.h"
# endif
#endif

#ifndef CONNECTIONSTORE_H_
#define CONNECTIONSTORE_H_

namespace zerosocket {
//#define MAXCONNECTION_SZ 10

/*
 * This class uses preprocessor time over loaded for different types of memory management
 * This class implements 3 types of storage for Connection object pointer.
 *!	- Simple array object, the search is linear and expensive as more connections are added
 *!			To use this type of store define  MAXCONNECTION_SZ to a meaningful number ( < 20)
 *!			eg. -DMAXCONNECTION_SZ=20
 *!		- if using large number of connections do no define MAXCONNECTION_SZ, and use either
 *!			a. STL std::map, (defaults)
 *!			b. Custom RB Tree implementation (using -DNOSTL), As of Aug 20, 2014 this part is unimplmented
 */
class RBNode;
class RBTree;
class ConnectionStore {
	friend class RBNode;
	friend class RBTree;
#ifdef MAXCONNECTION_SZ
	typedef struct {
		int connId;
		Descriptor* connObj;
	}ConnectionPair_t;
	ConnectionPair_t connmap [MAXCONNECTION_SZ];
#else
# ifndef NOSTL
	typedef std::map <int,Descriptor*> ConnectionMap_t;
	ConnectionMap_t hashmap;
# else
	RBTree hashmap;
# endif
#endif
public:
	typedef enum {
		CS_SUCCESS      = 0,
		CS_INVALIDPARAM = -1,
		CS_DUPLICATE_ID = -2
	}CS_Error_t;
	ConnectionStore();
	virtual ~ConnectionStore();
	Descriptor* get(int sockfd);
	int set(int sockfd, Descriptor * connobj);
	int purge(int sockfd);
	int purge(Descriptor * connobj);

	//getConnection compile time overload
protected:
#ifdef MAXCONNECTION_SZ
	Descriptor* getFromArr(int sockfd);
	int setToArr(int sockfd, Descriptor * connobj);
	int purgeFromArr(int sockfd);
#else
# ifndef NOSTL
	Descriptor* getFromHash(int sockfd);
	int setToHash(int sockfd, Descriptor * connobj);
	int purgeFromHash(int sockfd);
# else
	Descriptor* getFromTree(int sockfd);
	int setToTree(int sockfd, Descriptor * connobj);
	int purgeFromTree(int sockfd);
# endif
#endif


};

} /* namespace zerosocket */

#endif /* CONNECTIONSTORE_H_ */
