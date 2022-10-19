#include<keyboard_driver_asm.h>
#include<stdint.h>
#include <stdbool.h>
#include <interrupts.h>
#include <keyboard_driver.h>

static uint8_t scanCodeComplete = true;
static uint16_t currentScanCode;
static struct pressedKeys keyboardState;

static void addKeyPress(uint16_t scanCode)
{
	if(keyboardState.nbOfPressedKeys==4)
		return;
	for(int i = 0;i<keyboardState.nbOfPressedKeys;i++)
		if(keyboardState.keys[i] == scanCode)
			return;
	keyboardState.keys[keyboardState.nbOfPressedKeys] = scanCode;
	keyboardState.nbOfPressedKeys++;
	newInputToConsole(keyboardState);
	_sti();
}

static void removeKeyPress(uint16_t scanCode)
{
	for(int i =0;i<keyboardState.nbOfPressedKeys;i++)
	{
		if(keyboardState.keys[i] == scanCode)
		{
			for(int j=i;j<keyboardState.nbOfPressedKeys-1;j++)
			{
				keyboardState.keys[j] = keyboardState.keys[j+1];
			}
			keyboardState.nbOfPressedKeys--;
			break;
		}
	}
	newInputToConsole(keyboardState);
	_sti();
}

void initialiseKeyboard()
{

	setScanCodeSetToOne();

}

static void updateCurrentPressedKeys(uint16_t scan)
{
	//it's a one byte scancode
	if(!(scan & 0xFF00))
	{
		//we are releasing a key
		if(scan>0x80)	
		{
			scan-=0x80;
			//make sure the scan code is one that the driver handles
			if((scan<=0x3a && scan!=0 && scan!=0x29 && scan!=0x37)||scan==0x56)
				removeKeyPress(scan);
		}
		//we are pressing a key
		else
		{
			//make sure the scan code is one that the driver handles
			if((scan<=0x3a && scan !=0 && scan!=0x29 && scan!=0x37)||scan==0x56)
				addKeyPress(scan);	
		}
	}
	//it's a two byte scancode
	else
	{
		scan &= 0xFF;
		//we are releasing a key
		if(scan>0x80)
		{
			scan-=0x80;
			//make sure the scan code is one that the driver handles
			if(scan==0x38 || scan == 0x48 || scan == 0x4b || scan == 0x4d || scan == 0x50 || scan == 0x5b)
				removeKeyPress(scan);
		}
		//we are pressing a key
		else
		{
			//make sure the scan code is one that the driver handles
			if(scan==0x38 || scan == 0x48 || scan == 0x4b || scan == 0x4d || scan == 0x50 || scan == 0x5b)
				addKeyPress(scan);
		}
	}
}

void fetchKeyboardEvent()
{
	//we are disabling the interrupts 
	//to maintain the coherence of the keyboardState data structure
	_cli();

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
