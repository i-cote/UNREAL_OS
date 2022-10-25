#ifndef SYSCALLSAPI_H
#define SYSCALLSAPI_H

extern int sys_read_asm(int fd, char *buffer, int size);
extern int sys_write_asm(int fd, const char *buffer, int size);
extern int sys_print_asm(int fd, const char *buffer, int size, int coor);

#endif