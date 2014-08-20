/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#include "zerosocket.h"
#include "Config.h"

#ifndef INGRESS_H_
#define INGRESS_H_

namespace zerosocket {

/*!
 *@class Ingress
 * Ingress class object can be used to process incoming streams for zero socket header information,
 * uses JSMN parser to extract and store Config information. Use Ingress(Config*) contructor to provide
 * pointer to Config Object at runtime. do not use default constructor unless absolutely necessary
 *\anchor intro_sec
 *# Related Pages
 *[JSMN](md_src_jsmn__r_e_a_d_m_e.html)
 */
class Ingress {
	typedef struct {
		ZSElement element;
		char value[ZSMAXVALUSZ];
	} ElementValueList;
	Config * _config;
public:
	Ingress(Config * config);
	virtual ~Ingress();
	virtual unsigned char * getPayload(const unsigned char * data, size_t len);
	Config* getConfig() const;
	void setConfig(const Config* config);

protected:
	int processJSON(ElementValueList elemValList [] ,const char * header);
	int	json2Config (ElementValueList elemValList []);

	bool startsWith(const char * buff, int lookup, size_t len);
	bool endsWith(const char * buff, int lookup, size_t len);

};

} /* namespace zerosocket */

#endif /* INGRESS_H_ */
