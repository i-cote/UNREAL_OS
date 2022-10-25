#include <stdint.h>
#include <video.h>
#include <keyboard_driver.h>
#include <syscalls.h>
#include <console_driver.h>


static uint64_t (*syscalls[256]) (int,char *, int,int);

//Function pointers to the handlers


void initializeSyscallsArray() {
	syscalls[READ_PORT] = sys_read;
	syscalls[WRITE_PORT] = sys_write;
    syscalls[PRINT_PORT] = sys_print;
}


//arg is the number of syscall
void syscallHandler(int arg, int fd, char * str, int length, int coor){
	//The args are the following: rdi, rsi, rdx
	(*syscalls[arg])(fd, str, length,coor);
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

uint64_t sys_print(int fd, char * str, int length, int coor){
    switch (fd){
        case PLAYER_ONE:
            return printBlockAt(length,coor,red);
        case PLAYER_TWO:
            return printBlockAt(length,coor,blue);
        case CLEAR_SCREEN:
            setBackgroundColor();
        default:
            return -1;
    }
}