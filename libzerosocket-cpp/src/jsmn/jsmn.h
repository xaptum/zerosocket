#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef __JSMN_H_
#define __JSMN_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * JSON type identifier. Basic types are:
 * 	o Object
 * 	o Array
 * 	o String
 * 	o Other primitive: number, boolean (true/false) or null
 */
typedef enum {
	JSMN_PRIMITIVE = 0,
	JSMN_OBJECT = 1,
	JSMN_ARRAY = 2,
	JSMN_STRING = 3,
	JSMN_OPENOBJ = 16,
	JSMN_CLOSOBJ = 17,
	JSMN_OPENARR = 18,
	JSMN_CLOSARR = 19
} jsmntype_t;

typedef enum {
	/* Not enough tokens were provided */
	JSMN_ERROR_NOMEM = -1,
	/* Invalid character inside JSON string */
	JSMN_ERROR_INVAL = -2,
	/* The string is not a full JSON packet, more bytes expected */
	JSMN_ERROR_PART = -3,
} jsmnerr_t;

#define JSMN_MAX_LEVEL 10

/**
 * JSON token description.
 * @param		type	type (object, array, string etc.)
 * @param		start	start position in JSON data string
 * @param		end		end position in JSON data string
 */
typedef struct {
	jsmntype_t type;
	int start;
	int end;
	int size;
#ifdef JSMN_PARENT_LINKS
	int parent;
#endif
} jsmntok_t;

typedef union {
	int    pri;
	void * obj;
	void **arr;
	const char * str;
}jsmnval_t;

typedef struct {
#ifdef __cplusplus
public:
#endif
	size_t   alloclen;
	size_t   fill_len;
	size_t   noofstrs;
	uint16_t openobjs;
	uint16_t openarrs;
	jsmntype_t lastelemtype;
	char * buff;
	char closeout[JSMN_MAX_LEVEL]; // no more that 10 levels for now
}jsmn_composer;

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string
 */
typedef struct {
	unsigned int pos; /* offset in the JSON string */
	unsigned int toknext; /* next token to allocate */
	int toksuper; /* superior token node, e.g parent object or array */
} jsmn_parser;

/**
 * Create JSON parser over an array of tokens
 */
void jsmn_init(jsmn_parser *parser);

void jsmn_initc(jsmn_composer *composer);

/**
 * Run JSON parser. It parses a JSON data string into and array of tokens, each describing
 * a single JSON object.
 */
jsmnerr_t jsmn_parse(jsmn_parser *parser, const char *js, size_t len,
		jsmntok_t *tokens, unsigned int num_tokens);

/**
 * function uses internal memory management to decide how much space to pre allocate for buffer.
 * arguments:
 *   composer is the pointer to jsmn_compose * local variable ;
 *   		this helps make the function call thread-safe by containing all the states
 *   token is location of buffer containing token
 *   value is location of buffer containing a corresponding value
 *   type   represents the type of the value
 */
int32_t jsmn_compose(jsmn_composer *composer, const char * token, jsmnval_t value, jsmntype_t type);
/**
 * will close the
 */
int32_t jsmn_close(jsmn_composer *composer, size_t level );

/**
 * returns a escape safe string that can be included as another JSON string
 */
char * jsmn_safe_escape(jsmn_composer *composer);

#ifdef __cplusplus
}
#endif

#endif /* __JSMN_H_ */
