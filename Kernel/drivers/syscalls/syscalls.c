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
            printNewline();
            printString("stdin: ");
            /*//Now expecting for keyboardInterrupts
            while((c=buffer_read[0]) != '\n' && i < length){
                if(c == '\b'){
                    i-=2;
                    printChar(c);
                }
                else{
                    str[i] = c;
                    printChar(c);
                    i++;
                }
            }                            //ver como pasar una tecla del driver para poder usarla
            printNewline();
            str[i] = 0;
            return i;
            */
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