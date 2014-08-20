/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#include <strings.h>

#include "zerosocket.h"

#ifndef CONFIG_H_
#define CONFIG_H_

namespace zerosocket {

/*!
 * Base class implementation for persistent Config class, provides interface for setting and getting values
 *
 * @author Pradeep Barthur
 * @version 1.0
 * @date Aug 13, 2014
 * @bug no known bugs, report bugs to https://github.com/bladeninja/zerosocket/issues
 **/
class Config {
private:
	char * _config[SIZEOFARRAY(ZSElementName)];
protected: // Derived class, you have your rights here.
	virtual size_t read  (void * args) = 0;
	virtual size_t write (void * args) = 0;
public:
	Config();
	virtual ~Config();
	virtual const char * get (ZSElement element) const;
	virtual int set (ZSElement key,const char * val);
};

} /* namespace zerosocket */

#endif /* CONFIG_H_ */
