/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#ifndef ZEROSOCKET_H_
#define ZEROSOCKET_H_

enum ZSElement {
	ZUNK = 0,
	ZVER, // 1
	ZUSR, // 2
	ZPAS, // 3
	ZTOK, // 4
	ZDAT, // 5
	ZDID, // 6
	ZMET, // 7
	ZADR, // 8
	ZPRT, // 9
	ZORG, // 10
	ZDST  // 11
};

const char * const ZSElementName [] = { "UNKN", "zver", "zusr", "zpas", "ztok",
		"zdat", "zdid", "zmet", "zadr", "zprt" , "zorg" , "zdst" };

const char * const ZSElementDesc [] = {
		"UNKNOWN",
		"ProtocolVersion",
		"Username",
		"Password",
		"Token",
		"Date",
		"DeviceId",
		"Method",
		"Address",
		"Port",
		"Origin",
		"Destination"
	};

#define SIZEOFARRAY(ARR) sizeof(ARR)/sizeof(*ARR)

ZSElement getZSElementIndex(const char * name) ;

const char * getZSVersion(void);

#endif /* ZEROSOCKET_H_ */
