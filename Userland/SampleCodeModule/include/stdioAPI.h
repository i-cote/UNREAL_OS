#ifndef STDIOAPI_H
#define STDIOAPI_H

#include <stdarg.h>

void putChar(const char c);
char getChar();
int printf(const char* fmt, ...);
int scanf(const char* fmt, ...);
char* itoa(int num, char* str, int base);
void swap(char *x, char *y);
void reverse(char * str, int length);
void clearScreen();

#endif