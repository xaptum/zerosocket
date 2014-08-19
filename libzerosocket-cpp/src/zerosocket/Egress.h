/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/
#include "Config.h"
#ifndef EGRESS_H_
#define EGRESS_H_

namespace zerosocket {

/*
 *
 */
class Egress {
private:
	Config * _config;
public:
	Egress(Config * config);
	virtual ~Egress();
	char * c_str();
};

} /* namespace zerosocket */

#endif /* EGRESS_H_ */
