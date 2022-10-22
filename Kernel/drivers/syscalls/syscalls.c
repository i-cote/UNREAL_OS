#include <stdint.h>
#include <video.h>
#include <keyboard_driver.h>
#include <syscalls.h>

//Here all the syscall handler functions

uint64_t sys_read(int fd, char * str, int length){
   int i=0;
   uint8_t c;
   switch (fd)
   {
        case 1:
            printNewline();
            printString("stdin: ");
            /*while((c = fetchKeyboardEvent()) != '\n' && i < length){
                if (c != 0){
                    str[i] = c;
                    ncPrintChar(c);
                    i++;
                }
                if(c == '\b'){
                    i-=2;
                    ncPrintChar(c);
                }
            }*/       //ver como pasar una tecla del driver para poder usarla
            printNewline();
            str[i] = 0;
            return i;
        default:
            return -1;
    }
}


uint64_t sys_write(int fd, char * str, int length){
    switch (fd){
        case STDOUT:
            printNewline();
            printString(str);
            return length;
        case STDERR:
            printNewline();
            printStringColor(str, red);
            return length;
        default:
            return -1;
    }
}