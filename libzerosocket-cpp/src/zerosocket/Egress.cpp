/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: pradeepbarthur Inc.
 ********************************************************************************/

#include "jsmn.h"
#include "Egress.h"

namespace zerosocket {

Egress::Egress(Config* config)
	:_config(config)
{
}

/**
 * will not delete anything here.
 */
Egress::~Egress() {
}

#define PUSH_BACK(CMP,KEY,VAL) if(NULL != VAL){ \
			jsmnval_t KEY_; KEY_.str = VAL; \
			jsmn_compose(&CMP,#KEY, KEY_, JSMN_STRING); \
	}
/**
 * conver the Config object into string(char*)
 */

char* Egress::c_str() {
	jsmn_composer composer;
	jsmn_initc(&composer);

	PUSH_BACK(composer,ZUSR,_config->get(ZUSR));
	if (_config->get(ZTOK)){
		PUSH_BACK(composer,ZTOK,_config->get(ZTOK));
	}else{
		PUSH_BACK(composer,ZPAS,_config->get(ZPAS));
	}
	PUSH_BACK(composer,ZDAT,_config->get(ZDAT));
	PUSH_BACK(composer,ZDID,_config->get(ZDID));
	PUSH_BACK(composer,ZMET,_config->get(ZPAS));
	PUSH_BACK(composer,ZADR,_config->get(ZADR));
	PUSH_BACK(composer,ZPRT,_config->get(ZPRT));
	PUSH_BACK(composer,ZORG,_config->get(ZORG));
	PUSH_BACK(composer,ZDST,_config->get(ZDST));
	jsmn_close(&composer,JSMN_MAX_LEVEL);
	jsmn_safe_copy(&composer,";",1);
	return composer.buff;
}

} /* namespace zerosocket */
