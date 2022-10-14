#include<keyboard_driver_asm.h>
#include<stdint.h>
#include <stdbool.h>

static uint8_t scanCodeComplete = true;
static uint16_t currentScanCode;


void initialiseKeyboard()
{

	setScanCodeSetToOne();

}

void fetchKeyboardEvent()
{

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


}
