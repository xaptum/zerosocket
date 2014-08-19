/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 * 
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/

#include "jsmn.h"
#include "zerosocket.h"
#include "FileConfig.h"

namespace zerosocket {
/**
 * default constructor is protected, do not use unless you want to extend/derive
 */
FileConfig::FileConfig() {
}

FileConfig::FileConfig(const char* filename) {
	// copy the filename to local
	setFilename(filename);
}

FileConfig::FileConfig(FileConfig& config)
	:Config(config)
{
	this->setFilename(config.getFilename());
	_read();
}

/**
 * Destructor ensures that the file is flushed
 */
FileConfig::~FileConfig() {
	write(NULL);
}

/**
 * internal read implementation
 */
size_t FileConfig::_read() {
	size_t rsz = 0;
	size_t fsz = 0;
# ifdef NO_MALLOC
	char filecontent [20*MAX_FILEPATH_SIZE];
	fsz = 20*MAX_FILEPATH_SIZE;
# else
	char * filecontent;
# endif
	// open file,
	FILE * fh = fopen (this->getFilename(),"a+");

	// check open errors if any
	if (! fh) return -1;
	if (ferror(fh) != 0)return ferror(fh);

	// read content
# ifndef NO_MALLOC
	fseek (fh , 0 , SEEK_END);
	fsz = ftell (fh);
	filecontent = (char*) malloc (fsz+1);
	if (!filecontent) {perror("No memory available :");return -2;}
# endif
	rewind(fh);
	rsz = fread (filecontent,sizeof(char),fsz,fh);
	if (rsz <= 0){perror("Couldn't read file");return -3;}
	filecontent[rsz] = 0;
	// close
	fclose(fh);

	// parse file content
	this->_parser(filecontent,rsz);

# ifndef NO_MALLOC
	free(filecontent);
# endif
	return rsz;
}

/**
 * internal write implementation
 */
size_t FileConfig::_write() {
	size_t fsz = 0;
	size_t wsz = 0;
//# ifdef NO_MALLOC
//	char filecontent [20*MAX_FILEPATH_SIZE];
//	fsz = 20*MAX_FILEPATH_SIZE;
//# else // NOT YET IMPLEMENTED
	char * filecontent;
//# endif
	// open file,
	FILE * fh = fopen (this->getFilename(),"w"); // truncate the file content

	// check open errors if any
	if (! fh) return -1;
	if (ferror(fh) != 0)return ferror(fh);

	this->_composer(&filecontent,&fsz);
	if (fsz <= 0){fprintf(stderr,"Could not compose file content, debugging required");return fsz;}

	wsz = fwrite (filecontent,sizeof(char),fsz,fh);
	if (wsz <= 0){perror("Couldn't write to file");return wsz;}

	// close file
	fclose(fh);
# ifndef NO_MALLOC
	free(filecontent);
# endif
	return fsz;
}

/**
 * setter for filename, also used internally
 */
void FileConfig::setFilename(const char* filename) {
}

/**
 * getter for filename, also used internally
 */
const char* FileConfig::getFilename() const {
	return _filename;
}


size_t FileConfig::read(void* args) {
	return _read();
}

size_t FileConfig::_parser(char* filecontent,size_t size) {
	size_t retval = 0;
	jsmn_parser p;
	jsmntok_t tokens[128];
	jsmn_init(&p);
	bzero(tokens,sizeof(tokens));

	int ret = jsmn_parse(&p, filecontent, size, tokens, 128);
	if (ret < 0)
		return -1;

	for (int idx = 1; tokens[idx].end < tokens[0].end; idx += 2) {
		if (tokens[idx].type == JSMN_STRING || tokens[idx].type
				== JSMN_PRIMITIVE) {
			char name[100];
			strncpy(name, filecontent + tokens[idx].start, tokens[idx].end
					- tokens[idx].start);
			name[tokens[idx].end - tokens[idx].start] = 0;
			ZSElement elem = getZSElementIndex(name);
			if (ZUNK
					!= elem) {
				if (tokens[idx + 1].end < tokens[0].end) {
					char value[2048];
					// copy the token
					strncpy(value, filecontent + tokens[idx + 1].start, tokens[idx
					                                                      + 1].end - tokens[idx + 1].start);
					// set the string delim
					value[tokens[idx + 1].end - tokens[idx + 1].start] = 0;
					// set value and element in array in corresponding location
					//   and not incrementally as assumed before
					this->set(elem,newStrBuf(value));

				} else {
					fprintf(stderr,"something bad happened missing value after element %s\n",name );
					break;
				}
			}else if (0 == tokens[idx].end){
				break;
			} else {
				fprintf(stderr,"unknown element name : %s\n" , name);
			}
		}
	}
	return retval;
}

#define PUSH_BACK(CMP,KEY,VAL) if(NULL != VAL){ \
			jsmnval_t KEY_; KEY_.str = VAL; \
			jsmn_compose(&CMP,#KEY, KEY_, JSMN_STRING); \
	}
size_t FileConfig::_composer(char** filecontent,size_t * size) {
	jsmn_composer composer;
	jsmn_initc(&composer);

	PUSH_BACK(composer,ZUSR,this->get(ZUSR));
	PUSH_BACK(composer,ZPAS,this->get(ZPAS));
	PUSH_BACK(composer,ZTOK,this->get(ZTOK));
	PUSH_BACK(composer,ZDAT,this->get(ZDAT));
	PUSH_BACK(composer,ZDID,this->get(ZDID));
	PUSH_BACK(composer,ZMET,this->get(ZPAS));
	PUSH_BACK(composer,ZADR,this->get(ZADR));
	PUSH_BACK(composer,ZPRT,this->get(ZPRT));
	PUSH_BACK(composer,ZORG,this->get(ZORG));
	PUSH_BACK(composer,ZDST,this->get(ZDST));
	jsmn_close(&composer,JSMN_MAX_LEVEL);
	*filecontent = composer.buff;
	*size = composer.fill_len;
	return composer.fill_len;
}

char* FileConfig::newStrBuf(const char* old) {
	size_t sz = 0;
	char * retval = NULL;
	if (NULL == old) return NULL;
	sz = strlen(old);
	retval = new char[sz];
	strcpy(retval,old);
	return retval;
}

size_t FileConfig::write(void* args) {
	return _write();
}

} /* namespace zerosocket */
