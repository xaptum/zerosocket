/********************************************************************************
 * XAPTUM CONFIDENTIAL
 * ________________________________________________________________
 * 
 *  [2012] - [2014] Xaptum Incorporated 
 *  All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of Xaptum Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Xaptum Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Xaptum Incorporated.
 * 
 * /libzerosocket-cpp/src/zerosocket/Config.h
 * Config.h
 * 
 * Created on: Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#include <strings.h>

#include "zerosocket.h"

#ifndef CONFIG_H_
#define CONFIG_H_

namespace zerosocket {

/*
 * Base class for persistent Config
 * The class provides interface for setting and getting values
 */
class Config {
private:
	char * _config[SIZEOFARRAY(ZSElementName)];
protected: // Derived class, you have your rights here.
	virtual size_t read  (char * args) = 0;
	virtual size_t write (char * args) = 0;
public:
	Config();
	virtual ~Config();
	virtual const char * get (ZSElement element) const;
	virtual int set (ZSElement key,const char * val);
};

} /* namespace zerosocket */

#endif /* CONFIG_H_ */
