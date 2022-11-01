#ifndef _COLOR_H_
#define _COLOR_H_

//RGB colors to display in VESA screen. Anyway, framebuffer writes in memory in the following order: blue, green and red

#include <stdint.h>

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
} Color;

extern const Color white;
extern const Color red;
extern const Color lime;
extern const Color blue;
extern const Color yellow;
extern const Color green;
extern const Color gray;
extern const Color black;
extern const Color cyan;
extern const Color magenta;
extern const Color maroon;
extern const Color olive;
extern const Color purple;
extern const Color navy;
extern const Color pink;

#endif
