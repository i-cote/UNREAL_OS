#include <naiveConsole.h>
#include <keyboard_driver.h>
#include <console_mapper.h>
#include <video.h>

void newInputToConsole(const struct pressedKeys * keyboardState)
{
	const char * mapped_string = console_mapper(keyboardState);
	if(mapped_string)
		printString(mapped_string);
}
