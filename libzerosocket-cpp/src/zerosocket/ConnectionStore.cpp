/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/

#include <stdio.h>
#include "ConnectionStore.h"

namespace zerosocket {

ConnectionStore::ConnectionStore() {
#ifdef MAXCONNECTION_SZ
	// blank the array
	for (int idx = 0; idx < MAXCONNECTION_SZ ; idx ++)
	{
		connmap[idx].connId  = CS_INVALIDPARAM;
		connmap[idx].connObj = NULL;
	}
#else
# ifndef NOSTL
	Descriptor* getFromHash(int sockfd);
# else
	Descriptor* getFromTree(int sockfd);
# endif
#endif

}

/**
 * Deep destroy
 */
ConnectionStore::~ConnectionStore() {
#ifdef MAXCONNECTION_SZ
	for (int idx = 0; idx < MAXCONNECTION_SZ ; idx ++)
	{
		if (connmap[idx].connId != CS_INVALIDPARAM)
			delete connmap[idx].connObj;
	}
#else

#endif
}

/**
 * Overloaded get method
 */
Descriptor* ConnectionStore::get(int sockfd) {
#ifdef MAXCONNECTION_SZ
	return this->getFromArr(sockfd);
#else
# ifndef NOSTL
	return this->getFromHash(sockfd);
# else //# ifndef NOSTL
	return this->getFromTree(sockfd);
# endif // # ifndef NOSTL
#endif
}
#ifdef MAXCONNECTION_SZ
	Descriptor* ConnectionStore::getFromArr(int sockfd) {
		if (0 < sockfd) return NULL;
		for (int idx = 0; idx < MAXCONNECTION_SZ ; idx ++)
			if (sockfd == connmap[idx].connId)
				return connmap[idx].connObj;
		return NULL;
	}
#else
# ifndef NOSTL
	Descriptor* ConnectionStore::getFromHash(int sockfd) {
		ConnectionMap_t::const_iterator iter;
		if ((iter = hashmap.find(sockfd)) != hashmap.end())
		{
			return iter->second;
		}
		else
			return NULL;
	}
# else
	Descriptor* getFromTree(int sockfd)
	{

	}
# endif
#endif



/**
 * Set methods, does preprocessor compile time oveloading.
 * Refer to class documentation on how to choose the appropriate type
 *!@
 */
int ConnectionStore::set(int sockfd, Descriptor* connobj) {
	if (sockfd < 0 || connobj == NULL)
		return CS_INVALIDPARAM;
#ifdef MAXCONNECTION_SZ
	return this->setToArr(sockfd,connobj);
#else
# ifndef NOSTL
	return this->setToHash(sockfd,connobj);
# else //# ifndef NOSTL
	return this->setToTree(sockfd,connobj);
# endif // # ifndef NOSTL
#endif
}
#ifdef MAXCONNECTION_SZ
	int ConnectionStore::setToArr(int sockfd, Descriptor * connobj) {
		for (int idx = 0; idx < MAXCONNECTION_SZ ; idx ++)
			if (sockfd == connmap[idx].connId)
				return CS_DUPLICATE_ID;
			else if (CS_INVALIDPARAM == connmap[idx].connId) {
				connmap[idx].connId = sockfd;
				connmap[idx].connObj = connobj;
				return CS_SUCCESS;
			}

		return CS_INVALIDPARAM;
	}
#else
# ifndef NOSTL
	int ConnectionStore::setToHash(int sockfd, Descriptor * connobj) {
		if (hashmap.find(sockfd) == hashmap.end())
		{
			hashmap[sockfd] = connobj;
			return CS_SUCCESS;
		}
		else
			return CS_DUPLICATE_ID;
	}
# else
	int ConnectionStore::setToTree(int sockfd, Descriptor * connobj)
	{

	}
# endif
#endif


/**
 * Purge object from the list
 */

int ConnectionStore::purge(Descriptor* connobj) {
	if (connobj)
		return this->purge(connobj->getFd());
	else
		return CS_INVALIDPARAM;
}
int ConnectionStore::purge(int sockfd) {
#ifdef MAXCONNECTION_SZ
	return this->purgeFromArr(sockfd);
#else
# ifndef NOSTL
	return this->purgeFromHash(sockfd);
# else //# ifndef NOSTL
	return this->purgeFromTree(sockfd);
# endif // # ifndef NOSTL
#endif
}
#ifdef MAXCONNECTION_SZ
	int ConnectionStore::purgeFromArr(int sockfd) {
		Descriptor * obj = this->getFromArr(sockfd);
		if (obj) {
			for (int idx = 0; idx < MAXCONNECTION_SZ ; idx ++)
				if (sockfd == connmap[idx].connId)
				{
					delete connmap[idx].connObj;
					// retore struct to prestine state
					connmap[idx].connId = CS_INVALIDPARAM;
					connmap[idx].connObj= NULL;
					return CS_SUCCESS;
				}
				else
					return CS_INVALIDPARAM;
		}
		return CS_INVALIDPARAM;
	}
#else
# ifndef NOSTL
	int ConnectionStore::purgeFromHash(int sockfd) {
		ConnectionMap_t::iterator iter;
		if ((iter = hashmap.find(sockfd)) != hashmap.end())
		{
			delete iter->second;
			hashmap.erase(iter);
			return CS_SUCCESS;
		}
		return CS_INVALIDPARAM;
	}
# else
	int purgeFromTree(int sockfd)
	{

	}
# endif
#endif

} /* namespace zerosocket */
