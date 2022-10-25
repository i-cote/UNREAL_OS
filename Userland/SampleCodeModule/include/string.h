#ifndef STRING_H
#define STRING_H

#include <stdint.h>

char *strcpy(char *dest, const char *src);
char *strncopy(char *dest, const char *src, uint32_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, uint32_t n);
int strlen(const char *s);
int strtol(const char *str, char **endptr, int base);
char * my_strtok(char *srcString, char *delim);
unsigned int is_delim(char c, char *delim);

#endif