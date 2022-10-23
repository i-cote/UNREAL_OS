#include <time.h>
#include <video.h>

static unsigned long ticks = 0;

void timer_handler(void) {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
