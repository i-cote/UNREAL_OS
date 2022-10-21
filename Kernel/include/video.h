#ifndef _VIDEO_H
#define _VIDEO_H

#include <color.h>
#include <defs.h>

void * getPosToPrint(uint16_t x, uint16_t y);
void putPixel(uint16_t x, uint16_t y, Color color);
boolean checkValidPos();
void printChar();

#endif