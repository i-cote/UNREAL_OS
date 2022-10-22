#ifndef SYSCALLS_H_
#define SYSCALLS_H_

uint64_t sys_read(int fd, char * str, int length);
uint64_t sys_write(int fd, char * str, int length);

#endif