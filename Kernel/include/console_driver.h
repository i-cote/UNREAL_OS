#ifndef CONSOLE_DRIVER_H
#define CONSOLE_DRIVER_H
#include <keyboard_driver.h>
void newInputToConsole(const struct pressedKeys * keyboardState);
uint64_t read_from_console(void * dest,uint64_t count);
#endif
