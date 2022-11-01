
#include <stdint.h>
#include <color.h>
#include <defs.h>
#include <font.h>
#include <video.h>
#include <utf8_parser.h>
#include <font_manager.h>
#include <lib.h>


struct vbe_mode_info_structure
{
	uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;	  // deprecated
	uint8_t window_b;	  // deprecated
	uint16_t granularity; // deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;		   // number of bytes per horizontal line
	uint16_t width;		   // width in pixels
	uint16_t height;	   // height in pixels
	uint8_t w_char;		   // unused...
	uint8_t y_char;		   // ...
	uint8_t planes;
	uint8_t bpp;   // bits per pixel in this mode
	uint8_t banks; // deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__((packed));

// Current positions
uint16_t x = 0, y = 0;
Color default_background = {0,0,0};

void draw_bitmap(const void * bitmap, uint32_t x,uint32_t y, uint8_t width_in_bytes, uint8_t height_in_bytes, Color foreground, Color background)
{
	for(int i =0;i<height_in_bytes;i++)
	{
		for(int j=0;j<width_in_bytes;j++)
		{
			for(int k=0;k<8;k++)
			{
				if((*(((char*)bitmap)+i*width_in_bytes+j)) & (1<<(7-k)))
					putPixel(x+j*8+k,y+i,foreground);
				else
					putPixel(x+j*8+k,y+i,background);

			}
		}
	}
}

typedef struct vbe_mode_info_structure VBEModeInfoBlock;
static VBEModeInfoBlock *screen_data = (void *)0x5C00;

// The data type of the coordinates is according to the size of the screen
// Return the address of the xy position
void *getPosToPrint(uint16_t x, uint16_t y)
{
	// The 3 is because there is a difference of 3 addresses of 8bits each one for the colors. I mean we have a pixel every 3 bytes.
	return (void *)(screen_data->framebuffer + 3 * (x + (y * screen_data->width)));
}

boolean checkValidPos(uint16_t x, uint16_t y)
{
	return x >= screen_data->width || y >= screen_data->height;
}

void putPixel(uint16_t x, uint16_t y, Color color)
{
	if (checkValidPos(x, y) == true)
	{
		return;
	}
	// I get the position of the buffer
	Color *pos = (Color *)getPosToPrint(x, y);
	// Print moment
	*pos = color;
}

// Sets the background color
void setBackgroundColor()
{
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			putPixel((uint16_t)i, (uint16_t)j, default_background);
		}
	}
	x = 0;
	y = 0;
}

void printChar(char c)
{
	print_utf8((utf8_sequence)(&c),1, white);
}

void printNewline()
{
	x = 0;
	y += get_font_glyph_height();
	if (y > screen_data->height - get_font_glyph_height())
	{
		setBackgroundColor();
		y = 0;
	}
}

void print_utf8(utf8_sequence utf8,uint64_t count,Color color)
{
	if (count==1 && *utf8 == '\n')
	{
		printNewline();
		return;
	}
	if(count==1 && *utf8==0x7f)
	{
		x-=get_font_glyph_width();
		void * bitmap_pointer = get_bitmap_pointer((utf8_sequence)" ",1);
		draw_bitmap(bitmap_pointer,x,y,get_font_glyph_width()/8,get_font_glyph_height(),color,default_background);
		return;
	
	}

	void * bitmap_pointer = get_bitmap_pointer(utf8,count);
	if(bitmap_pointer==(void *)0)
		return;
	draw_bitmap(bitmap_pointer,x,y,get_font_glyph_width()/8,get_font_glyph_height(),color,default_background);
	x += get_font_glyph_width();
	if (x > screen_data->width - get_font_glyph_width())
		printNewline();
}
int64_t check_console_driver_commands(const char * command)
{
	if(memcompare(command,"\x1b\x5bsetFontSize",strlen("\x1b\x5bsetFontSize"))==0)
	{
		const char * size = command+strlen("\x1b\x5bsetFontSize ");
		if(memcompare(size,"8",1) == 0)
			set_font(8);
		else if (memcompare(size,"14",2) == 0)
			set_font(14);
		else if (memcompare(size,"16",2) == 0)
			set_font(16);
		else if (memcompare(size,"32",2) == 0)
			set_font(32);
		return 0;
	}
	return -1;
}

void printStringColor(char *str, Color color)
{
	//Initialise font to default font
	static int font_initialised = 0;
	if(!font_initialised)
	{
		initialise_font();
		font_initialised = 1;
	}

	if(check_console_driver_commands(str)==0)
		return;
	uint64_t count = strlen(str);
	int64_t old_index = 0;
	int64_t new_index = 0;
	while(count>0)
	{
		new_index = utf8_index((utf8_sequence)str,count);
		if(new_index>=0)
		{
			print_utf8((utf8_sequence)str,new_index+1,color);
			str += (new_index+1);
			count -= (new_index+1);
		}
		else
		{
			print_utf8((utf8_sequence)"�",strlen("�"),color);
			return;
		}
		old_index += new_index+1;
	}
}

void printString(char *string)
{
	//Initialise font to default font
	static int font_initialised = 0;
	if(!font_initialised)
	{
		initialise_font();
		font_initialised = 1;
	}
	printStringColor(string, white);
}

void printDec(uint64_t n)
{
	if (n == 0)
	{
		printChar('0');
		return;
	}

	uint64_t aux = n;
	uint8_t digits = 0;
	while (aux > 0)
	{
		digits++;
		aux /= 10;
	}

	char str[digits + 1];
	str[digits] = '\0';
	for (int i = digits - 1; i >= 0; i--)
	{
		str[i] = '0' + n % 10;
		n /= 10;
	}

	printString(str);
}

void printHex(uint64_t n)
{
	printString("0x");
	if (n == 0)
	{
		printChar('0');
		return;
	}

	uint64_t aux = n;
	uint8_t digits = 0;
	while (aux > 0)
	{
		digits++;
		aux /= 16;
	}

	char str[digits + 1];
	str[digits] = '\0';
	for (int i = digits - 1; i >= 0; i--)
	{
		uint8_t digit = n % 16;
		if (digit < 10)
			str[i] = '0' + digit;
		else
			str[i] = 'A' + digit - 10;
		n /= 16;
	}

	printString(str);
}

void printBlockColor(Color color) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			putPixel(x+j, y+i, color);
		}
	}
	x += CHAR_HEIGHT;
	if (x > screen_data->width - CHAR_HEIGHT)
		printNewline();
}

int printBlockAt(uint16_t x_coor, uint16_t y_coor, Color color) {

	if (x_coor > screen_data->width - BLOCK_SIZE || y_coor > screen_data->height - BLOCK_SIZE || x_coor < 0 || y_coor < 0) {
		return 1;
	}
	for (int i = 0; i < BLOCK_SIZE; i++) {
		for (int j = 0; j < BLOCK_SIZE; j++) {
			Color * check_pos = (Color *)getPosToPrint(x_coor+j, y_coor+i);
			if (check_pos->r != black.r || check_pos->g != black.g || check_pos->b != black.b) {
				return 1;
			}
			putPixel(x_coor+j, y_coor+i, color);
		}
	}
	return 0;
}
