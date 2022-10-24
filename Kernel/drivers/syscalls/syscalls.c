#include <stdint.h>
#include <video.h>
#include <keyboard_driver.h>
#include <syscalls.h>
#include <console_driver.h>


static uint64_t (*syscalls[256]) (int,char *, int);

//Function pointers to the handlers


void initializeSyscallsArray() {
	syscalls[READ_PORT] = sys_read;
	syscalls[WRITE_PORT] = sys_write;
}


//arg is the number of syscall
void syscallHandler(int arg, int fd, char * str, int length){
	//The args are the following: rdi, rsi, rdx
	(*syscalls[arg])(fd, str, length);
}

//Here all the syscall handler functions

//In this case, *str is the buffer and lenght his dim
uint64_t sys_read(int fd, char * str, int length){
   int i=0;
   char c;
   switch (fd)
   {
        case STDIN:
			return read_from_console(str,length);
        default:
            return -1;
    }
}


uint64_t sys_write(int fd, char * str, int length){
    switch (fd){
        case STDOUT:
            printString(str);
            return length;
        case STDERR:
            printStringColor(str, red);
            return length;
        default:
            return -1;
    }
}
