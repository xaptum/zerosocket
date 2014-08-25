#include <stdlib.h>
#include <stdio.h>
#include "jsmn.h"

static size_t alloc_sz = 1024;
/**
 * Allocates a fresh unused token from the token pull.
 */
static jsmntok_t *jsmn_alloc_token(jsmn_parser *parser, 
		jsmntok_t *tokens, size_t num_tokens) {
	jsmntok_t *tok;
	if (parser->toknext >= num_tokens) {
		return NULL;
	}
	tok = &tokens[parser->toknext++];
	tok->start = tok->end = -1;
	tok->size = 0;
#ifdef JSMN_PARENT_LINKS
	tok->parent = -1;
#endif
	return tok;
}

/**
 * Fills token type and boundaries.
 */
static void jsmn_fill_token(jsmntok_t *token, jsmntype_t type, 
                            int start, int end) {
	token->type = type;
	token->start = start;
	token->end = end;
	token->size = 0;
}

/**
 * Fills next available token with JSON primitive.
 */
static jsmnerr_t jsmn_parse_primitive(jsmn_parser *parser, const char *js,
		size_t len, jsmntok_t *tokens, size_t num_tokens) {
	jsmntok_t *token;
	int start;

	start = parser->pos;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		switch (js[parser->pos]) {
#ifndef JSMN_STRICT
			/* In strict mode primitive must be followed by "," or "}" or "]" */
			case ':':
#endif
			case '\t' : case '\r' : case '\n' : case ' ' :
			case ','  : case ']'  : case '}' :
				goto found;
		}
		if (js[parser->pos] < 32 || js[parser->pos] >= 127) {
			parser->pos = start;
			return JSMN_ERROR_INVAL;
		}
	}
#ifdef JSMN_STRICT
	/* In strict mode primitive must be followed by a comma/object/array */
	parser->pos = start;
	return JSMN_ERROR_PART;
#endif

found:
	if (tokens == NULL) {
		parser->pos--;
		return 0;
	}
	token = jsmn_alloc_token(parser, tokens, num_tokens);
	if (token == NULL) {
		parser->pos = start;
		return JSMN_ERROR_NOMEM;
	}
	jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
#ifdef JSMN_PARENT_LINKS
	token->parent = parser->toksuper;
#endif
	parser->pos--;
	return 0;
}

/**
 * Filsl next token with JSON string.
 */
static jsmnerr_t jsmn_parse_string(jsmn_parser *parser, const char *js,
		size_t len, jsmntok_t *tokens, size_t num_tokens) {
	jsmntok_t *token;

	int start = parser->pos;

	parser->pos++;

	/* Skip starting quote */
	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		char c = js[parser->pos];

		/* Quote: end of string */
		if (c == '\"' || c == '\'') {
			if (tokens == NULL) {
				return 0;
			}
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL) {
				parser->pos = start;
				return JSMN_ERROR_NOMEM;
			}
			jsmn_fill_token(token, JSMN_STRING, start+1, parser->pos);
#ifdef JSMN_PARENT_LINKS
			token->parent = parser->toksuper;
#endif
			return 0;
		}

		/* Backslash: Quoted symbol expected */
		if (c == '\\') {
			parser->pos++;
			switch (js[parser->pos]) {
				/* Allowed escaped symbols */
				case '\'': case '\"': case '/' : case '\\' : case 'b' :
				case 'f' : case 'r' : case 'n'  : case 't' :
					break;
				/* Allows escaped symbol \uXXXX */
				case 'u':
					parser->pos++;
					int i = 0;
					for(; i < 4 && js[parser->pos] != '\0'; i++) {
						/* If it isn't a hex character we have an error */
						if(!((js[parser->pos] >= 48 && js[parser->pos] <= 57) || /* 0-9 */
									(js[parser->pos] >= 65 && js[parser->pos] <= 70) || /* A-F */
									(js[parser->pos] >= 97 && js[parser->pos] <= 102))) { /* a-f */
							parser->pos = start;
							return JSMN_ERROR_INVAL;
						}
						parser->pos++;
					}
					parser->pos--;
					break;
				/* Unexpected symbol */
				default:
					parser->pos = start;
					return JSMN_ERROR_INVAL;
			}
		}
	}
	parser->pos = start;
	return JSMN_ERROR_PART;
}

/**
 * Parse JSON string and fill tokens.
 */
jsmnerr_t jsmn_parse(jsmn_parser *parser, const char *js, size_t len,
		jsmntok_t *tokens, unsigned int num_tokens) {
	jsmnerr_t r;
	int i;
	jsmntok_t *token;
	int count = 0;

	for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
		char c;
		jsmntype_t type;

		c = js[parser->pos];
		switch (c) {
			case '{': case '[':
				count++;
				if (tokens == NULL) {
					break;
				}
				token = jsmn_alloc_token(parser, tokens, num_tokens);
				if (token == NULL)
					return JSMN_ERROR_NOMEM;
				if (parser->toksuper != -1) {
					tokens[parser->toksuper].size++;
#ifdef JSMN_PARENT_LINKS
					token->parent = parser->toksuper;
#endif
				}
				token->type = (c == '{' ? JSMN_OBJECT : JSMN_ARRAY);
				token->start = parser->pos;
				parser->toksuper = parser->toknext - 1;
				break;
			case '}': case ']':
				if (tokens == NULL)
					break;
				type = (c == '}' ? JSMN_OBJECT : JSMN_ARRAY);
#ifdef JSMN_PARENT_LINKS
				if (parser->toknext < 1) {
					return JSMN_ERROR_INVAL;
				}
				token = &tokens[parser->toknext - 1];
				for (;;) {
					if (token->start != -1 && token->end == -1) {
						if (token->type != type) {
							return JSMN_ERROR_INVAL;
						}
						token->end = parser->pos + 1;
						parser->toksuper = token->parent;
						break;
					}
					if (token->parent == -1) {
						break;
					}
					token = &tokens[token->parent];
				}
#else
				for (i = parser->toknext - 1; i >= 0; i--) {
					token = &tokens[i];
					if (token->start != -1 && token->end == -1) {
						if (token->type != type) {
							return JSMN_ERROR_INVAL;
						}
						parser->toksuper = -1;
						token->end = parser->pos + 1;
						break;
					}
				}
				/* Error if unmatched closing bracket */
				if (i == -1) return JSMN_ERROR_INVAL;
				for (; i >= 0; i--) {
					token = &tokens[i];
					if (token->start != -1 && token->end == -1) {
						parser->toksuper = i;
						break;
					}
				}
#endif
				break;
			case '\'':
			case '\"':
				r = jsmn_parse_string(parser, js, len, tokens, num_tokens);
				if (r < 0) return r;
				count++;
				if (parser->toksuper != -1 && tokens != NULL)
					tokens[parser->toksuper].size++;
				break;
			case '\t' : case '\r' : case '\n' : case ':' : case ',': case ' ': 
				break;
#ifdef JSMN_STRICT
			/* In strict mode primitives are: numbers and booleans */
			case '-': case '0': case '1' : case '2': case '3' : case '4':
			case '5': case '6': case '7' : case '8': case '9':
			case 't': case 'f': case 'n' :
#else
			/* In non-strict mode every unquoted value is a primitive */
			default:
#endif
				r = jsmn_parse_primitive(parser, js, len, tokens, num_tokens);
				if (r < 0) return r;
				count++;
				if (parser->toksuper != -1 && tokens != NULL)
					tokens[parser->toksuper].size++;
				break;

#ifdef JSMN_STRICT
			/* Unexpected char in strict mode */
			default:
				return JSMN_ERROR_INVAL;
#endif
		}
	}

	for (i = parser->toknext - 1; i >= 0; i--) {
		/* Unmatched opened object or array */
		if (tokens[i].start != -1 && tokens[i].end == -1) {
			return JSMN_ERROR_PART;
		}
	}

	return count;
}

/**
 * Creates a new parser based over a given  buffer with an array of tokens 
 * available.
 */
void jsmn_init(jsmn_parser *parser) {
	parser->pos = 0;
	parser->toknext = 0;
	parser->toksuper = -1;
}

void jsmn_initc(jsmn_composer * composer)
{
	composer->alloclen = 0;
	composer->fill_len = 0;
	composer->noofstrs = 0;
	composer->lastelemtype = JSMN_PRIMITIVE;
	composer->openobjs = 0;
	composer->openarrs = 0;
	composer->buff     = NULL;
	memset(composer->closeout,0,sizeof(composer->closeout));
}



/**
 * internal functions
 */
size_t _jsmn_safe_copy  (jsmn_composer * composer,const char * ibuff, size_t ilen);
size_t _jsmn_compose_pri(jsmn_composer * composer, const char * token, jsmnval_t value);
size_t _jsmn_compose_arr(jsmn_composer * composer, const char * token, jsmnval_t value);
size_t _jsmn_compose_obj(jsmn_composer * composer, const char * token, jsmnval_t value);
size_t _jsmn_compose_str(jsmn_composer * composer, const char * token, jsmnval_t value);

/*!
 * external function to add content to the composer, use with care, preferably after jsmn_close()
 * @param composer the pointer to jsmn_composer object,
 * @param ibuff buffer containing extra content
 * @param ilen  size of content in ibuff
 * @return size of content copied
 */
inline size_t jsmn_safe_copy  (jsmn_composer * composer,const char * ibuff, size_t ilen)
{
	return _jsmn_safe_copy  (composer,ibuff,ilen);
}
/**
 *
 */
int32_t jsmn_compose(jsmn_composer * composer, const char * token, jsmnval_t value, jsmntype_t type)
{
	if (NULL == composer || NULL == token)
		return JSMN_ERROR_NOMEM;
// 1. check if space was allocated previously, else allocate now
	//either 0 start of operation
	if (0 == composer->alloclen || NULL == composer->buff)
	{
		composer->buff		= malloc (alloc_sz);
		if (! composer->buff) return JSMN_ERROR_NOMEM;
		composer->alloclen	= alloc_sz;
		composer->fill_len = sprintf(composer->buff,"{"); // only known sprintf as it is the first time
		composer->openobjs++;
		composer->lastelemtype = JSMN_OPENOBJ;
		strncat(composer->closeout,"}", 10);
	}
	switch (type) {
	case JSMN_PRIMITIVE: {
		if (_jsmn_compose_pri(composer,token,value) > 0)
			composer->lastelemtype = JSMN_PRIMITIVE;
		}
		break;
	case JSMN_OBJECT: {
			// not implemented
		}
		break;
	case JSMN_ARRAY: {
			// not implemented
		}
		break;
	case JSMN_OPENARR: {
		if (_jsmn_compose_obj(composer,token,value) > 0)
			composer->lastelemtype = JSMN_OPENARR;
		}
		break;
	case JSMN_OPENOBJ: {
		if (_jsmn_compose_obj(composer,token,value) > 0)
			composer->lastelemtype = JSMN_OPENOBJ;
		}
		break;
	case JSMN_STRING:
	default: {
		if (_jsmn_compose_str(composer,token,value) > 0)
			composer->lastelemtype = JSMN_STRING;
		}
		break;
	} // END - switch (type){

	return 0;
}


size_t _jsmn_compose_pri(jsmn_composer * composer, const char * token, jsmnval_t value)
{
	char  ibuff[1024];
	size_t ilen;
	char demark = ' ';
	switch(composer->lastelemtype){
	case	JSMN_OPENOBJ:
	case	JSMN_OPENARR:
		demark = ' ';
		break;
	default:
		demark = ',';
		break;
	}
	ilen = snprintf(ibuff,sizeof(ibuff),"%c\"%s\":%d",demark,token,value.pri);
	return _jsmn_safe_copy(composer,ibuff,ilen);
}
size_t _jsmn_compose_arr(jsmn_composer * composer, const char * token, jsmnval_t value)
{
	char  ibuff[1024];
	size_t ilen;
	char demark=' ';
	switch(composer->lastelemtype){
	case	JSMN_OPENOBJ:
	case	JSMN_OPENARR:
		demark = ' ';
		break;
	default:
		demark = ',';
		break;
	}
	ilen = snprintf(ibuff,sizeof(ibuff),"%c\"%s\":[",demark,token);
	composer->noofstrs ++;
	strncat(composer->closeout,"]", 10);
	return _jsmn_safe_copy(composer,ibuff,ilen);
}
size_t _jsmn_compose_obj(jsmn_composer * composer, const char * token, jsmnval_t value)
{
	char  ibuff[1024];
	size_t ilen;
	char demark=' ';
	switch(composer->lastelemtype){
	case	JSMN_OPENOBJ:
	case	JSMN_OPENARR:
		demark = ' ';
		break;
	default:
		demark = ',';
		break;
	}
	ilen = snprintf(ibuff,sizeof(ibuff),"%c\"%s\":{",demark,token);
	composer->noofstrs ++;
	strncat(composer->closeout,"}", 10);
	return _jsmn_safe_copy(composer,ibuff,ilen);
}
/**
 * buff will be no more that 1024
 */
size_t _jsmn_compose_str(jsmn_composer * composer, const char * token, jsmnval_t value)
{
	char  ibuff[1024];
	size_t ilen;
	char demark=' ';
	switch(composer->lastelemtype){
	case	JSMN_OPENOBJ:
	case	JSMN_OPENARR:
		demark = ' ';
		break;
	default:
		demark = ',';
		break;
	}
	ilen = snprintf(ibuff,sizeof(ibuff),"%c\"%s\":\"%s\"",demark,token,value.str);
	composer->noofstrs ++;
	return _jsmn_safe_copy(composer,ibuff,ilen);
}

size_t _jsmn_safe_copy(jsmn_composer * composer,const char * ibuff, size_t ilen)
{
	if (composer->alloclen-composer->fill_len < ilen+1){
		size_t nlen  = composer->alloclen + alloc_sz;
		char * nbuff = realloc (composer->buff,nlen);
		if (NULL == nbuff) return JSMN_ERROR_NOMEM;
		composer->buff = nbuff;
		composer->alloclen = nlen;
	//}else{
		// we need no re allocate
	}
	memcpy(composer->buff+composer->fill_len,ibuff,ilen);
	composer->fill_len += ilen;
	composer->buff[composer->fill_len] = 0;
	return ilen;
}

/**
 * check return value before proceeding, if NULL, there was an error.
 */
char * jsmn_safe_escape(jsmn_composer *composer)
{
	char * newbuff = NULL;
	char * newbend = NULL;
	size_t newbfsz = 0;
	char * origend = NULL;
	char * origbuf = NULL;
	if (! composer ) return NULL;

	newbfsz = (composer->alloclen < composer->fill_len + (composer->noofstrs * 4))?
			composer->alloclen + alloc_sz: composer->alloclen;
	// do we need to allocate more space than intended !
	newbuff = (char*) malloc(newbfsz);

	if (!newbuff) return NULL;
	// run thru the original buff
	for (origbuf = composer->buff , origend = composer->buff + composer->fill_len ,
			newbend = newbuff; newbfsz > 0 && origbuf <= origend  ; --newbfsz){
		switch (*origbuf)
		{
		case '\'':
		case '\"':
			*(newbend++) = '\\';
		default:// increment newbend , origbuf
			*(newbend++) = *(origbuf++);
			break;
		}
	}
	*(newbend++) = '\0';
	return newbuff;
}

int32_t jsmn_close(jsmn_composer *composer, size_t level )
{
	char * eos = NULL;
	jsmntype_t previous = JSMN_PRIMITIVE;
	for (eos = composer->closeout + strlen(composer->closeout) -1 ; level > 0 && eos >= composer->closeout ; --level, -- eos){
		_jsmn_safe_copy(composer,eos,1);
		if (*eos == '}') previous = JSMN_CLOSOBJ;
		else if (*eos == ']') previous = JSMN_CLOSARR;
		*eos = '\0';
	}
	return 0;
}
