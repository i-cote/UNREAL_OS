
#include <stdint.h>
#include <color.h>
#include <defs.h>
#include <font.h>
#include <video.h>


struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
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
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed)); 


//Current positions
uint16_t x = 0, y = 0;

typedef struct vbe_mode_info_structure VBEModeInfoBlock;
static VBEModeInfoBlock * screen_data = (void *)0x5C00;


//The data type of the coordinates is according to the size of the screen
//Return the address of the xy position 
void * getPosToPrint(uint16_t x, uint16_t y){
	//The 3 is because there is a difference of 3 addresses of 8bits each one for the colors. I mean we have a pixel every 3 bytes. 
	return (void *) (screen_data->framebuffer + 3 * (x + (y * screen_data->width)));
}

boolean checkValidPos(uint16_t x, uint16_t y){
	return x>=screen_data->width || y>=screen_data->height; 
}

void putPixel(uint16_t x, uint16_t y, Color color){
	if(checkValidPos(x,y) == true){
		return;
	}
	//I get the position of the buffer
	Color * pos = (Color *) getPosToPrint(x, y);
	//Print moment
	*pos = color;
}

void setBackgroundColor(){
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			putPixel((uint16_t)i,(uint16_t)j, black);
		}
		
	}
	
}

void printCharColor(char c, Color color){
	if (c == '\n') {
        printNewline();
        return;
    }

    if (c >= FIRST_CHAR && c <= LAST_CHAR) {
	    const char* data = font + 32*(c-33);
	    for (int h=0; h<16; h++) {
    		Color* pos = (Color*)getPosToPrint(x, y+h);
    		if (*data & 0b00000001) pos[0] = color;
    		if (*data & 0b00000010) pos[1] = color;
    		if (*data & 0b00000100) pos[2] = color;
    		if (*data & 0b00001000) pos[3] = color;
    		if (*data & 0b00010000) pos[4] = color;
    		if (*data & 0b00100000) pos[5] = color;
    		if (*data & 0b01000000) pos[6] = color;
    		if (*data & 0b10000000) pos[7] = color;
    		data++;
    		if (*data & 0b00000001) pos[8] = color;
    		data++;
    	}
    }

    x += CHAR_WIDTH;
    if (x > screen_data->width - CHAR_WIDTH)
        printNewline();
}

void printChar(char c) {
    printCharColor(c, white);
}

void printNewline() {
	x = 0;
	y += CHAR_HEIGHT;
	if (y > screen_data->height - CHAR_HEIGHT){
		setBackgroundColor();
		y=0;
	}
}

void printStringColor(char * str, Color color){
	while(*str != '\0'){
		printCharColor(*str, color);
		str++;
	}
}

void printString(char * string) {
	printStringColor(string, white);
}

void printDec(uint64_t n) {
	if (n == 0) {
		printChar('0');
		return;
	}

	uint64_t aux = n;
	uint8_t digits = 0;
	while (aux > 0) {
		digits++;
		aux /= 10;
	}

	char str[digits+1];
	str[digits] = '\0';
	for (int i = digits-1; i >= 0; i--) {
		str[i] = '0' + n % 10;
		n /= 10;
	}

	printString(str);
}

void printHex(uint64_t n) {
	printString("0x");
	if (n == 0) {
		printChar('0');
		return;
	}

	uint64_t aux = n;
	uint8_t digits = 0;
	while (aux > 0) {
		digits++;
		aux /= 16;
	}

	char str[digits+1];
	str[digits] = '\0';
	for (int i = digits-1; i >= 0; i--) {
		uint8_t digit = n % 16;
		if (digit < 10)
			str[i] = '0' + digit;
		else
			str[i] = 'A' + digit - 10;
		n /= 16;
	}

	printString(str);
}

void printBlock() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			putPixel(x+j, y+i, white);
		}
	}
	x += 16;
	if (x > screen_data->width - 16)
		printNewline();
}


