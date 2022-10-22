#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#define STDOUT 1
#define STDERR 2

uint64_t sys_read(int fd, char * str, int length);
uint64_t sys_write(int fd, char * str, int length);

#endif