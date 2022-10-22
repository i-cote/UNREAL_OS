#include <stdint.h>
#include <keyboard_driver.h>
#include <time.h>
#include <syscalls.h>
#include <irqDispatcher.h>

static void int_20();
static void int_21();
static void int_80(int arg, int fd, char * str, int length);


static uint64_t (*functions[256]) (int, int, char *, int);
static uint64_t (*syscalls[256]) (int,char *, int);

void irqDispatcher(uint64_t irq, int arg, int fd, char * str, int length){
	(*functions[irq + 0x20])(arg, fd, str, length);
}

void initializeIrqFunctionsArray() {
	
	functions[0x20] = int_20;
	functions[0x21] = int_21;
	functions[0x80] = int_80;

}

void initializeSyscallsArray() {
	syscalls[0x00] = sys_read;
	syscalls[0x01] = sys_write;
}

void int_20() {
	timer_handler();
}

void int_21(){
	fetchKeyboardEvent();
}

void int_80(int arg, int fd, char * str, int length){
	(*syscalls[arg])(fd, str, length);
}


