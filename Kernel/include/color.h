#ifndef _COLOR_H_
#define _COLOR_H_

//RGB colors to display in VESA screen. Anyway, framebuffer writes in memory in the following order: blue, green and red

#include <stdint.h>

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} Color;

extern Color white;
extern Color red;
extern Color lime;
extern Color blue;
extern Color yellow;
extern Color green;
extern Color gray;
extern Color black;
extern Color cyan;
extern Color magenta;
extern Color maroon;
extern Color olive;
extern Color purple;
extern Color navy;

#endif