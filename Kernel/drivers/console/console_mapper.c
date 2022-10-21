#include <keyboard_driver.h>

#define UNDEF (char*)0
#define STATE_CHANGE_KEY (char*)0
#define SIZE_MAIN_MAP 0x56
#define SIZE_SHIFT_MAP SIZE_MAIN_MAP
#define MAIN_MAP_HASH(X) ((X)-1)
#define SHIFT_MAP_HASH(X) ((X)-1)
#define WITHIN_BOUNDS(INDEX,ARRAY_SIZE) (((INDEX)>=0)&&((INDEX)<(ARRAY_SIZE)))

struct special_keys
{
	uint16_t shift_left;
	uint16_t shift_right;
	uint16_t crtl;
	uint16_t alt_gr;
	uint16_t cmd;
	uint16_t caps_lock;
};

struct language_mapping 
{
	const char * main_map[SIZE_MAIN_MAP];
	const char * shift_map[SIZE_SHIFT_MAP];
	const struct special_keys specialKeys;
};

#include "argentinian.consolemap.h"
#include "french.consolemap.h"


static struct language_mapping * current_language_mapping = &ar_mapping;

const char * console_mapper (const struct pressedKeys * keyboardState)
{
	if(keyboardState->nbOfPressedKeys==1)
	{
		uint16_t keycode = MAIN_MAP_HASH(keyboardState->keys[0]);
		if(!WITHIN_BOUNDS(keycode,SIZE_MAIN_MAP))
			return UNDEF;
		if(current_language_mapping->main_map[keycode] == UNDEF)
			return UNDEF;
		return current_language_mapping->main_map[keycode];
	}
	else if(keyboardState->nbOfPressedKeys==2)
	{
		uint16_t specialKey = keyboardState->keys[0];
		if(specialKey==0)
			return UNDEF;

		if(specialKey == current_language_mapping->specialKeys.shift_right || specialKey == current_language_mapping->specialKeys.shift_left)
		{
			uint16_t keycode = SHIFT_MAP_HASH(keyboardState->keys[1]);
			if(!WITHIN_BOUNDS(keycode,SIZE_SHIFT_MAP))
				return UNDEF;
			if(current_language_mapping->shift_map[keycode] == UNDEF)
				return UNDEF;
			return current_language_mapping->shift_map[keycode];
		
		}
		else if(specialKey == current_language_mapping->specialKeys.crtl)
		{
		
		}
		else if(specialKey == current_language_mapping->specialKeys.alt_gr)
		{
		
		}
	}
	return UNDEF;
}
