/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#include "Config.h"

#ifndef INGRESS_H_
#define INGRESS_H_

namespace zerosocket {

/*
 *
 */
class Ingress {
	Config * _config;
public:
	Ingress(Config * config);
	virtual ~Ingress();
};

} /* namespace zerosocket */

#endif /* INGRESS_H_ */
