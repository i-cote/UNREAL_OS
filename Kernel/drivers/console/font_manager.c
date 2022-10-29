#include <stdint.h>
#include <utf8_parser.h>
#include <psfu.h>
#include <font_manager.h>
#include <lib.h>
#define DEFAULT_FONT_SIZE 32
 
typedef struct {PSF_font * start;void * end;} FONT_FILE;
static FONT_FILE * font_file;
static void * bitmap_array;
static utf8_sequence * unicode_table;

void set_font(uint8_t font_size)
{

	if(font_size==8)
	{
		font_file->start = (PSF_font *)&_binary_drivers_console_fonts_lat1_08_psfu_start;
		font_file->end = (void *)&_binary_drivers_console_fonts_lat1_08_psfu_end;
	}
	else if(font_size==10)
	{
		font_file->start = (PSF_font *)&_binary_drivers_console_fonts_lat1_10_psfu_start;
		font_file->end = (void *)&_binary_drivers_console_fonts_lat1_10_psfu_end;
	}
	else if(font_size==12)
	{
		font_file->start = (PSF_font *)&_binary_drivers_console_fonts_lat1_12_psfu_start;
		font_file->end = (void *)&_binary_drivers_console_fonts_lat1_12_psfu_end;
	}
	else if(font_size==14)
	{
		font_file->start = (PSF_font *)&_binary_drivers_console_fonts_lat1_14_psfu_start;
		font_file->end = (void *)&_binary_drivers_console_fonts_lat1_14_psfu_end;
	}
	else if(font_size==16)
	{
		font_file->start = (PSF_font *)&_binary_drivers_console_fonts_lat1_16_psfu_start;
		font_file->end = (void *)&_binary_drivers_console_fonts_lat1_16_psfu_end;
	}
	else if(font_size==32)
	{
		font_file->start = (PSF_font *)&_binary_drivers_console_fonts_latarcyrheb_sun32_psfu_start;
		font_file->end = (void *)&_binary_drivers_console_fonts_latarcyrheb_sun32_psfu_end;
	}
	else
		return;

	bitmap_array = (void *)font_file->start+font_file->start->headersize;

	unicode_table = (utf8_sequence *)(bitmap_array+font_file->start->numglyph*font_file->start->bytesperglyph);

	//TODO repaint the whole screen to show change of font

}
uint32_t get_font_glyph_width()
{
	return font_file->start->width;
}
uint32_t get_font_glyph_height() 
{
	return font_file->start->height;
}



static uint8_t get_size_of_current_utf8_in_unicode_table(void * pointer_in_unicode_table,void * font_file_end)
{
	return utf8_index(pointer_in_unicode_table,font_file_end-pointer_in_unicode_table)+1;
}

void * get_bitmap_pointer(const utf8_sequence utf8,uint8_t len)
{
	void * ret = (void *)0;
	void * start_of_current_utf8_in_unicode_table = unicode_table;
	uint32_t index_in_unicode_table = 0;
	uint8_t size_of_current_utf8_in_unicode_table = 0;
	while(start_of_current_utf8_in_unicode_table<font_file->end)
	{
		size_of_current_utf8_in_unicode_table = get_size_of_current_utf8_in_unicode_table 
			(start_of_current_utf8_in_unicode_table,font_file->end);
		if(size_of_current_utf8_in_unicode_table==len && memcompare(start_of_current_utf8_in_unicode_table,utf8,len)==0)
		{
			ret = bitmap_array + index_in_unicode_table*font_file->start->bytesperglyph;
			return ret;
		}
		if(((uint8_t*)start_of_current_utf8_in_unicode_table)[size_of_current_utf8_in_unicode_table]==0xff)
		{
			index_in_unicode_table++;
			start_of_current_utf8_in_unicode_table += (size_of_current_utf8_in_unicode_table+1);
		}
		else
			start_of_current_utf8_in_unicode_table += (size_of_current_utf8_in_unicode_table);
	}
	return ret;
}
