#ifndef SYSCALLSAPI_H
#define SYSCALLSAPI_H

#define STDIN  1
#define STDOUT 1
#define STDERR 2


#define GET_TICKS 0
#define GET_SECONDS 1
#define GET_TIME 2

extern int sys_read_asm(int fd, char *buffer, int size);
extern int sys_write_asm(int fd, const char *buffer, int size);
extern int sys_print_asm(int fd, const char *buffer, int size, int coor);
extern int sys_ticker_asm(int fd, int length);

#endif