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

#ifndef MAX_FILEPATH_SIZE
# define MAX_FILEPATH_SIZE 1024
#endif
/*
 *
 */
class FileConfig: public Config {
private:
	// members
	char _filename[MAX_FILEPATH_SIZE];
	// methods
	size_t _read ();
	size_t _parser(char * filecontent,size_t size);
	size_t _write ();
	size_t _composer(char ** filecontent,size_t * size);
public:
	FileConfig(const char * filename);
	FileConfig(FileConfig & config);
	virtual ~FileConfig();
	void setFilename(const char * filename);
	const char* getFilename() const;
	static char * newStrBuf(const char * old);

protected:
	FileConfig();
	virtual size_t read  (void * args);
	virtual size_t write (void * args);
};

} /* namespace zerosocket */

#endif /* FILECONFIG_H_ */
