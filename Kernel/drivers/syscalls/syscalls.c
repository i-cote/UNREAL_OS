#include <stdint.h>
#include <naiveConsole.h>
#include <keyboard_driver.h>


uint64_t sys_read(int fd, char * str, int length){
   int i=0;
   uint8_t c;
   switch (fd)
   {
        case 1:
            ncNewline();
            ncPrint("stdin: ");
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
            ncNewline();
            str[i] = 0;
            return i;
        default:
            return -1;
    }
}

uint64_t sys_write(int fd, char * str, int length){
    switch (fd){
        case 1:
            ncNewline();
            ncPrint(str);
            return length;
        case 2:
            ncNewline();
            //ncPrintAttribute(str, 0x04);
            return length;
        default:
            return -1;
    }
}