#ifndef KEYBOARD_DRIVER_H_
#define KEYBOARD_DRIVER_H_
#include <stdint.h>
void fetchKeyboardEvent();
struct pressedKeys
{
	uint16_t keys[4];
	uint8_t nbOfPressedKeys;
};
#endif /*KEYBOARD_DRIVER_H_*/
