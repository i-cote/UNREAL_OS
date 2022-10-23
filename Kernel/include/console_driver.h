
#ifndef CONSOLE_DRIVER_H
#define CONSOLE_DRIVER_H

#include <keyboard_driver.h>

static char buffer_read[1];

void newInputToConsole(const struct pressedKeys * keyboardState);

#endif
