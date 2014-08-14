/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#ifndef FILECONFIG_H_
#define FILECONFIG_H_

#include "Config.h"

namespace zerosocket {

/*
 *
 */
class FileConfig: public Config {
public:
	FileConfig();
	virtual ~FileConfig();
};

} /* namespace zerosocket */

#endif /* FILECONFIG_H_ */
