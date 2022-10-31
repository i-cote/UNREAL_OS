#ifndef STDIOAPI_H
#define STDIOAPI_H

#include <stdarg.h>
#include <stdint.h>
#include <color.h>

void putChar(const char c);
char getChar();
int printfColor(const char* fmt, Color color, ...);
int scanf(const char* fmt, ...);
char* itoa(int num, char* str, int base);
void swap(char *x, char *y);
void reverse(char * str, int length);
void clearScreen();
uint32_t hex2int(char *hex);

#endif