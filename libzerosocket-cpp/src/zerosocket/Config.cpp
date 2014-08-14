/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeep barthur
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "version.h"
#include "Config.h"
#include "zerosocket.h"

namespace zerosocket {

Config::Config()
{
	for (size_t idx = 0 ; idx < SIZEOFARRAY(ZSElementName) ; idx ++)
	{
		_config[idx] = NULL;
	}
	_config[ZVER] = const_cast<char *>(_version);
}

/**
 * Destructor will detroy any and all allocated memory and resources from this class forward
 * use -DNO_MANAGE_MEMORY to change destructor behavior at compile time
 */
Config::~Config() {
#ifdef NO_MANAGE_MEMORY
	// nothing to delete. application manages memory
#else
	for (size_t idx = 0 ; idx < SIZEOFARRAY(ZSElementName) ; idx ++)
	{
		if ( ZVER == idx) continue; // skip version as it is a static string
		if ( NULL != _config[idx])
		{
			delete _config[idx];
			_config[idx] = NULL;
		}
	}
#endif
}

/**
 * returns the value corresponding to the key provided
 */
const char* Config::get(ZSElement key) const {
	if (key >= SIZEOFARRAY(ZSElementName) || key <= 0) return NULL;
	return _config[key];
}

/**
 * Set the element config array.
 * this method will
 * CAUTION: always use NEW char [...] to create the buffer, do not provide malloc'd
 * or pointer from std::string.c_str()
 * to change behavior and manage memory from the application use -DNO_MANAGE_MEMORY
 * @return
 */
int Config::set(ZSElement key, const char* val) {
	if (key >= SIZEOFARRAY(ZSElementName) || key <= 0) return -1;
	if (NULL == val) return -2;
	_config[key] = const_cast<char *>(val);
	return 0;
}

} /* namespace zerosocket */

