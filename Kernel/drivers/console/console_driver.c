#include <keyboard_driver.h>
#include <console_mapper.h>
#include <video.h>
#include <lib.h>
#include <stdint.h>
#define READ_BUFFER_SIZE_MAX 100

static char console_read_buffer[READ_BUFFER_SIZE_MAX];
static char * buffer_read_start = console_read_buffer;
static char * buffer_read_end = console_read_buffer;
static uint8_t console_read_buffer_size;

void newInputToConsole(const struct pressedKeys * keyboardState)
{
	const char * mapped_utf8 = console_mapper(keyboardState);
	if(mapped_utf8)
	{
		uint8_t utf8_size = strlen(mapped_utf8);
		utf8_size = utf8_size + console_read_buffer_size > READ_BUFFER_SIZE_MAX ?READ_BUFFER_SIZE_MAX-console_read_buffer_size:utf8_size;
		for(int i =0;i<utf8_size;i++)
		{
			buffer_read_end[0] = mapped_utf8[i];
			buffer_read_end = console_read_buffer+((buffer_read_end-console_read_buffer+1)%READ_BUFFER_SIZE_MAX);
		}
		console_read_buffer_size+=utf8_size;
	}
}


uint64_t read_from_console(void * dest,uint64_t count)
{

	count = count>console_read_buffer_size?console_read_buffer_size:count;
	for(int i = 0;i<count;i++)
	{
		((char*)dest)[i] = buffer_read_start[0];
		buffer_read_start = console_read_buffer+((buffer_read_start-console_read_buffer+1)%READ_BUFFER_SIZE_MAX);
	}
	console_read_buffer_size-=count;
	return count;
}
