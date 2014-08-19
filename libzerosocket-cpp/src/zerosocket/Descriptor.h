/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
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
