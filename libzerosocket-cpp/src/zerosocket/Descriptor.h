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
 * /libzerosocket-cpp/src/zerosocket/Descriptor.h
 * Descriptor.h
 * 
 * Created on: Aug 18, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

namespace zerosocket {

/*
 *
 */
class Descriptor {
public:
	Descriptor();
	virtual ~Descriptor();
	virtual void setFd(int fd) = 0;
	virtual int getFd() const = 0;
};

} /* namespace zerosocket */

#endif /* DESCRIPTOR_H_ */
