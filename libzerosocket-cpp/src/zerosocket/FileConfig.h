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
 * /libzerosocket-cpp/src/zerosocket/FileConfig.h
 * FileConfig.h
 * 
 * Created on: Aug 13, 2014
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
