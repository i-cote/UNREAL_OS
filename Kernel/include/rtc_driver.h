#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H
#include <stdint.h>
struct TIME {

	uint32_t hour;
	uint32_t minute;
	uint32_t second;

};
void get_time(struct TIME * time);
void print_time(struct TIME * time);
void initialize_time();
#endif
