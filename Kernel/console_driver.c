#include <keyboard_driver.h>
#include <naiveConsole.h>
#define KEYCODE_NOT_DEFINED (char*)0
#define STATE_CHANGE_KEY (char*)0

const char * fr_key_map [] = {
"\x1b"/*escape*/,
"&","é",
"\x22"/*double quotes*/,
"\x27"/*single quotes*/,
"(","-","è","_","ç","à",")","=",
"\x7f"/*backspace*/,
"\x09"/*tab*/,
"a","z","e","r","t","y","u","i","o","p",
(char *)0,/*^ not implemented by our console*/
"$",
"\x0d"/*enter*/,
STATE_CHANGE_KEY,/*crtl*/
"q","s","d","f","g","h","j","k","l","m","ù",
(char *)0,/*² not implemented by our console*/
STATE_CHANGE_KEY,/*shift left*/
"*","w","x","c","v","b","n",",",";",":","!",
STATE_CHANGE_KEY,/*shift right*/
KEYCODE_NOT_DEFINED,/*keycode 0x37 not defined*/
STATE_CHANGE_KEY,/*alt*/
" ",
STATE_CHANGE_KEY,/*caps lock*/

KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,

"<"
};


const char * fr_key_map_shift [] = {
"\x1b"/*escape*/,
"1","2","3","4","5","6","7","8","9","0","°","+",
"\x7f"/*backspace*/,
"\x09"/*tab*/,
"A","Z","E","R","T","Y","U","I","O","P",
(char *)0,/*¨ not implemented by our console*/
"£",
"\x0d"/*enter*/,
STATE_CHANGE_KEY,/*crtl*/
"Q","S","D","F","G","H","J","K","L","M","%","~",
STATE_CHANGE_KEY,/*shift left*/
"µ","W","X","C","V","B","N","?",".","/","§",
STATE_CHANGE_KEY,/*shift right*/
KEYCODE_NOT_DEFINED,/*keycode 0x37 not defined*/
STATE_CHANGE_KEY,/*alt*/
" ",
STATE_CHANGE_KEY,/*caps lock*/

KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,
">"
};

const char * ar_key_map [] = {
"\x1b"/*escape*/,
"1","2","3","4",
"5","6","7","8","9","0","-","=",
"\x7f"/*backspace*/,
"\x09"/*tab*/,
"q","w","e","r","t","y","u","i","o","p","[","]",
"\x0d"/*enter*/,
STATE_CHANGE_KEY,/*crtl*/
"a","s","d","f","g","h","j","k","l",";","'",
"`",
STATE_CHANGE_KEY,/*shift left*/
"\\","z","x","c","v","b","n","m",",",".","/",
STATE_CHANGE_KEY,/*shift right*/
STATE_CHANGE_KEY,/*keycode 0x37 not defined*/
STATE_CHANGE_KEY,/*alt*/
" ",
STATE_CHANGE_KEY,/*caps lock*/

KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,KEYCODE_NOT_DEFINED,

"<"
};


void newInputToConsole(struct pressedKeys keyboardState)
{
	if(keyboardState.nbOfPressedKeys==1 && keyboardState.keys[0]>=1 && keyboardState.keys[0]<=0x56 && fr_key_map[keyboardState.keys[0]-1]!=0)
	{
		ncPrint(fr_key_map[keyboardState.keys[0]-1]);
	}
	else if(keyboardState.nbOfPressedKeys==2 && (keyboardState.keys[0]==0x36 || keyboardState.keys[0]==0x2a) && keyboardState.keys[1]>=1 && keyboardState.keys[1]<=0x56 && fr_key_map[keyboardState.keys[1]-1]!=0)
	{
		ncPrint(fr_key_map_shift[keyboardState.keys[1]-1]);
	}
}
