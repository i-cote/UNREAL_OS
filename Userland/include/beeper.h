#ifndef BEEPER_H_
#define BEEPER_H_
#include <stdint.h>
void play_sound(uint32_t nFrequence);
void nosound();
void beep();
void rickroll();
void timer_wait(int t);


#endif