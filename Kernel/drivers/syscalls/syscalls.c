#include <stdint.h>
#include <video.h>
#include <keyboard_driver.h>
#include <syscalls.h>
#include <console_driver.h>
#include <time.h>
#include <lib.h>


static uint64_t (*syscalls[256]) (int,char *, int,int,uint32_t *);

//Function pointers to the handlers


void initializeSyscallsArray() {
	syscalls[READ_PORT] = sys_read;
	syscalls[WRITE_PORT] = sys_write;
    syscalls[PRINT_PORT] = sys_print;
    syscalls[TICKER_PORT] = sys_ticker;
    syscalls[MEMCPY_PORT] = sys_memcpy;
}


//arg is the number of syscall
void syscallHandler(int arg, int fd, char * str, int length, int coor, uint32_t * dest){
	//The args are the following: rdi, rsi, rdx
	(*syscalls[arg])(fd, str, length,coor,dest);
}

//Here all the syscall handler functions

//In this case, *str is the buffer and lenght his dim
uint64_t sys_read(int fd, char * str, int length){
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

uint64_t sys_print(int fd, int length, int coor){
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

uint64_t sys_ticker(int fd, int length){
    switch (fd){
        case GET_TICKS:
            return ticks_elapsed();
        case GET_SECONDS:
            return seconds_elapsed();
        case GET_TIME:
            return time_elapsed(length);
        default:
            return -1;
    }
}

uint64_t sys_memcpy(uint32_t * dest, int length){
    //void * ans = memcpy(dest,VECTOR DE LOS REGISTROS, length);
    return 0;
}