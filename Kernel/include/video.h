#ifndef _VIDEO_H
#define _VIDEO_H

#include <color.h>
#include <defs.h>

/* The width of a character in pixels. */
#define CHAR_WIDTH 9
/* The height of a character in pixels. */
#define CHAR_HEIGHT 16

void * getPosToPrint(uint16_t x, uint16_t y);
void putPixel(uint16_t x, uint16_t y, Color color);
boolean checkValidPos(uint16_t x, uint16_t y);
void printChar(char c);

#endif