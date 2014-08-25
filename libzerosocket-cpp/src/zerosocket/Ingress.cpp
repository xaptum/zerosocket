/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/
#include <ctype.h>
#include <string.h>
#include "jsmn.h"
#include "Ingress.h"

namespace zerosocket {

size_t Ingress::maxheader_sz = 10240;

Ingress::Ingress(Config * config)
	:_config(config)
{
}

Ingress::~Ingress() {
}

/*!
 * Logic: processes the payload by detecting zero socket header
 * 	- parse the header information
 * 	- process the json object
 * 	- Business logic to store json elements in config
 * 	- remove the header
 *@param data the raw data as read from socket
 *@param len the length of data read
 *@return pointer to the location of payload without zerosocket header,
 *			use this pointer to find the payload length (return - data)
 */
Ingress::StateHeader_t
Ingress::getPayload(const unsigned char* data, size_t len) {
	ElementValueList elemValList [SIZEOFARRAY(ZSElementName)];
	int updated = 0;
	memset(elemValList,0,sizeof(elemValList));

	if (!data) return StateHeader_t(NotReadable,NULL);

	// extract header part
<<<<<<< HEAD
	if ( ! startsWith((const char *)data,'{',len))
		return StateHeader_t(HeaderMissing, const_cast<unsigned char *>(data));

	// check for end of header
=======
	if ( ! startsWith((const char *)data,'{',len)) return const_cast<unsigned char *>(data);
>>>>>>> branch 'master' of https://github.com/bladeninja/zerosocket.git
	unsigned char * endOfHdr = (unsigned char*) strchr(reinterpret_cast<const char*>(data),';');
<<<<<<< HEAD
	if (NULL == endOfHdr)
		return StateHeader_t(HeaderIncomplete, const_cast<unsigned char *>(data)); // no header found

	//Check if it indeed is a header
	if ( ! endsWith((const char *)endOfHdr,'}',endOfHdr-data) )
		return StateHeader_t(HeaderMissing, const_cast<unsigned char *>(data));
=======
	if (NULL == endOfHdr) return const_cast<unsigned char *>(data); // no header found
	if ( ! endsWith((const char *)endOfHdr,'}',endOfHdr-data) ) return const_cast<unsigned char *>(data);
>>>>>>> branch 'master' of https://github.com/bladeninja/zerosocket.git
	*endOfHdr = 0;

	// process JSON
	if (processJSON(elemValList,reinterpret_cast<const char*>(data)) < 0)
	{
		fprintf(stderr,"error processing ");
<<<<<<< HEAD
		return StateHeader_t(HeaderIncomplete, const_cast<unsigned char *>(data));
=======
		return const_cast<unsigned char *>(data);
>>>>>>> branch 'master' of https://github.com/bladeninja/zerosocket.git
	}
	updated = json2Config(elemValList);
	fprintf(stderr,"%d config elements updated\n",updated);
	return StateHeader_t( HeaderComplete, ++endOfHdr);
}

/*!
 * parses the JSON object and extracts the zero socket header information
 */
int Ingress::processJSON(ElementValueList elemValList [] ,const char * header) {
	int retval = 0;
	size_t hdrlen = strlen(header);
	jsmn_parser p;
	jsmntok_t tokens[128];
	jsmn_init(&p);

	bzero(tokens,sizeof(tokens));

	retval = jsmn_parse(&p, header, hdrlen, tokens, 128);
	if (retval < 0)
		return -1;

	for (int idx = 1; tokens[idx].end < tokens[0].end; idx += 2) {
		if (tokens[idx].type == JSMN_STRING || tokens[idx].type == JSMN_PRIMITIVE)
		{
			char name[ZSMAXNAMESZ];
			strncpy(name, header + tokens[idx].start, tokens[idx].end
					- tokens[idx].start);
			name[tokens[idx].end - tokens[idx].start] = 0;
			ZSElement elem = getZSElementIndex(name);
			if (ZUNK != elem) {
				if (tokens[idx + 1].end < tokens[0].end) {
					elemValList[elem].element = elem;
					// copy the token
					strncpy(elemValList[elem].value, header + tokens[idx + 1].start,
							tokens[idx + 1].end - tokens[idx + 1].start);
					// set the string delim
					elemValList[elem].value[tokens[idx + 1].end - tokens[idx + 1].start] = 0;
					// set value and element in array in corresponding location
					//   and not incrementally as assumed before
				} else {
					fprintf (stderr,"something bad happened missing value after element %s\n",
							name );
					return -1;
					break;
				}
			}else if (0 == tokens[idx].end){
				break;
			} else {
				//
				fprintf (stderr,"unknown element name : %s\n", name );
			}
		}
	}
	return 0;
}

/*!
 * Logic: process the ElementValueList array
 * 	check if the zero socket header element was sent from server
 * 		if set,  check if the value is not the same as set previously
 * 			set the new config
 * TODO: this operation is unsafe as it contains a strdup without check,
 * needs a check before Config.set() operation
 *@param elemValList is an pointer to array of type ElementValueList
 */
int
Ingress::json2Config (ElementValueList elemValList [])
{
	ElementValueList * list = elemValList;
	int retval = 0;
	if (NULL == list) return -1;
	for (size_t idx = 0 ; idx < SIZEOFARRAY(ZSElementName) ; idx ++, list++)
	{
		if ( list->element > ZUNK){
			const char * val = getConfig()->get(list->element);
			if (NULL != val)
			{// contains a valid pointer, check if we need to update
				if (0 == strcmp(val,list->value))
					continue; // skip setting new buffer,
			}
			// this is quite unsafe
			getConfig()->set(list->element,strdup(list->value));
			++retval;
		}
	}
	return retval;
}

/*!
 * hoping the compiler will do some optimization for idx/counter
 */
bool Ingress::startsWith(const char* buff, int lookup, size_t len) {
	for (size_t idx ; idx < len ; idx ++, buff++)
	{
		if (isspace(*buff) ) continue;
		else if (lookup == *buff) return true;
		else return false;
	}
	return false;
}

/*!
 * hoping the compiler will do some optimization for idx/counter
 */
bool Ingress::endsWith(const char* buff, int lookup, size_t len) {
	for (size_t idx ; idx < len ; idx ++, buff--)
	{
		if (isspace(*buff) ) continue;
		else if (lookup == *buff) return true;
		else return false;
	}
	return false;
}

Config* Ingress::getConfig() const {
	return _config;
}

void Ingress::setConfig(const Config* config) {
	_config = const_cast<Config*>(config);
}

} /* namespace zerosocket */

