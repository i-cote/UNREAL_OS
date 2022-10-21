#include <rtc_driver.h>
#include <naiveConsole.h>
void _startClock();
void _stopClock();
uint32_t _getCurrentHours();
uint32_t _getCurrentMinutes();
uint32_t _getCurrentSeconds();
void _setHours();
void _setMinutes();
void _setSeconds();

void initialize_time()
{
	_stopClock();
	_setHours();
	_setMinutes();
	_setSeconds();
	_startClock();
}

void get_time(struct TIME * time)
{
	_stopClock();
	time->hour = _getCurrentHours();
	time->minute = _getCurrentMinutes();
	time->second = _getCurrentSeconds();
	_startClock();
}

void print_time(struct TIME * time)
{

	ncPrintDec((uint64_t)time->hour);
	ncPrint(":");
	ncPrintDec((uint64_t)time->minute);
	ncPrint(":");
	ncPrintDec((uint64_t)time->second);
	ncNewline();
}
