#ifndef UTF8_PARSER
#define UTF8_PARSER
#include <stdint.h>
typedef uint8_t * utf8_sequence;
int8_t utf8_index(const unsigned char * s, uint32_t len);
#endif
