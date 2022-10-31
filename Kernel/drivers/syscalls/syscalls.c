#include <stdint.h>
#include <video.h>
#include <keyboard_driver.h>
#include <syscalls.h>
#include <console_driver.h>
#include <time.h>
#include <lib.h>
#include <color.h>

extern uint64_t registerBuffer;

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


uint64_t sys_write(int fd, char * str, int length, Color color){
    switch (fd){
        case STDOUT:
            printStringColor(str, color);
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

uint64_t sys_memcpy(uint64_t * dest, int length){
    memcpy(dest,&registerBuffer, length * sizeof(uint64_t));
    return 0;
}