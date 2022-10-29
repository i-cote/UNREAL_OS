#ifndef CONSOLE_UTF8_MAPPER_H
#define CONSOLE_UTF8_MAPPER_H
#include <utf8_parser.h>
void set_font(uint8_t font_size);
uint32_t get_font_glyph_width();
uint32_t get_font_glyph_height();
void * get_bitmap_pointer(const utf8_sequence utf8,uint8_t len);
#endif
