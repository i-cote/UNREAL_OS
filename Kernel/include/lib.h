#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
uint64_t * memcompare(void * s1, void * s2, uint64_t length);
uint64_t strlen(const char *s);

char *cpuVendor(char *result);

#endif
