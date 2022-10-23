#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#define STDIN  1
#define STDOUT 1
#define STDERR 2

#define READ_PORT 0x00
#define WRITE_PORT 0x01

uint64_t sys_read(int fd, char * str, int length);
uint64_t sys_write(int fd, char * str, int length);

#endif