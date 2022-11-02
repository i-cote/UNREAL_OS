#include<keyboard_driver_asm.h>
#include<stdint.h>
#include <stdbool.h>
#include <interrupts.h>
#include <keyboard_driver.h>
#include <console_driver.h>

static uint8_t scanCodeComplete = true;
static uint16_t currentScanCode;
static struct pressedKeys keyboardState;

//Adds a key press to the keyboardState data structure
//Arguments : the scan-code of the the key being pressed
static void addKeyPress(uint16_t scanCode)
{
	if(keyboardState.nbOfPressedKeys==4)
		return;
	for(int i = 0;i<keyboardState.nbOfPressedKeys;i++)
		if(keyboardState.keys[i] == scanCode)
		{
			//Showing the input in console	
			newInputToConsole(&keyboardState);
			return;
		}
	keyboardState.keys[keyboardState.nbOfPressedKeys] = scanCode;
	keyboardState.nbOfPressedKeys++;
	//Showing the input in console	
	newInputToConsole(&keyboardState);
	_sti();
}

//Removes a key press from the keyboardState date structure
//Arguments : the pressed version scan-code of the key
static void removeKeyPress(uint16_t scanCode)
{
	for(int i =0;i<keyboardState.nbOfPressedKeys;i++)
		if(keyboardState.keys[i] == scanCode)
		{
			for(int j=i;j<keyboardState.nbOfPressedKeys-1;j++)
				keyboardState.keys[j] = keyboardState.keys[j+1];
			keyboardState.nbOfPressedKeys--;
			break;
		}

	//Showing the input in console	
	newInputToConsole(&keyboardState);
	_sti();
}


//Checks whether the scan-code is for releasing or pressing
//Arguments: el escancode recibido por fetchKeyboardEvent()
static void updateCurrentPressedKeys(uint16_t scan)
{
	if((scan&0xFF)>0x80)
		removeKeyPress(scan-0x80);
	else
		addKeyPress(scan);
}

//This is the keyboard handler!!!
void fetchKeyboardEvent()
{
	//we are disabling the interrupts 
	//to maintain the coherence of the keyboardState data structure
	_cli();
	//Reading the scancode for port 60h (keyboard_driver_asm)
	uint8_t scanCodeByte = fetchScanCodeByte();

	//if the fetched byte is the first byte of the scan code
	if(scanCodeComplete)
	{
	
		//if the first byte that we set is 0xE0
		//we consider that we have a 2-byte scan code so we wait for the 
		//second byte
		if(scanCodeByte==0xE0)
		{
		
			currentScanCode = scanCodeByte << 8;
			scanCodeComplete = false;
			_sti();
			return;
		
		}
		//if the first byte is not 0xE0 then we consider
		//we have a one-byte scan code and so the scancode is complete
		else
		{
		
			currentScanCode = scanCodeByte;
			scanCodeComplete = true;
		
		}
	}
	
	//the fecthed byte is the second of a two-byte scan-code
	else
	{
		currentScanCode |= scanCodeByte; 	
		scanCodeComplete = true;
		
	}

	updateCurrentPressedKeys(currentScanCode);
}
