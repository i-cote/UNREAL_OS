#include <beeper.h>
#include <syscallsAPI.h>
#include <stdioAPI.h>

//Play sound using built in speaker
 void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
	if(nFrequence){
        //Set the PIT to the desired frequency
 		Div = 1193180 / nFrequence;
 		sys_out_asm(0x43, 0xb6);
 		sys_out_asm(0x42, (uint8_t) (Div) );
 		sys_out_asm(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 		tmp = sys_inb_asm(0x61);
  		if (tmp != (tmp | 3)) {
 		sys_out_asm(0x61, tmp | 3);
 		}
	}
	else
	{
		nosound();
	}
	
 }
 
 //make it shutup
 void nosound() {
 	uint8_t tmp = sys_inb_asm(0x61) & 0xFC;
 	sys_out_asm(0x61, tmp);
 }
 
 //Make a beep
 void beep() {
    play_sound(1000);
    timer_wait(50);
    nosound();
 }

 void timer_wait(int t){
    int i = sys_ticker_asm(GET_TICKS,0);
	printfColor("BEEP", red);
    while(sys_ticker_asm(GET_TICKS,0) < i + t){}
 }