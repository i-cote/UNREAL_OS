#ifndef _VIDEO_H
#define _VIDEO_H

#include <color.h>
#include <defs.h>
#include<utf8_parser.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

/* The width of a character in pixels. */
#define CHAR_WIDTH 9
/* The height of a character in pixels. */
#define CHAR_HEIGHT 16
/* The size of a block in Tron */
#define BLOCK_SIZE 10


void * getPosToPrint(uint16_t x, uint16_t y);
void putPixel(uint16_t x, uint16_t y, Color color);
boolean checkValidPos(uint16_t x, uint16_t y);
void printChar(char c);
void setBackgroundColor();
void printNewline();
void printString(char * string);
void printCharColor(char c, Color color);
void printStringColor(char * str, Color color);
void printDec(uint64_t num);
void printHex(uint64_t num);
void printBlock(int size, uint16_t x, uint16_t y);
void printCharWithSize(char c, int size);
int printBlockAt(uint16_t x_coor, uint16_t y_coor, Color color);
void print_utf8(utf8_sequence utf8,uint64_t count,Color color);

#endif
