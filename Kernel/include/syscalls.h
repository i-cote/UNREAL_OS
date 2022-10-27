#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#define STDIN  1
#define STDOUT 1
#define STDERR 2

#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define CLEAR_SCREEN 3

#define GET_TICKS 0
#define GET_SECONDS 1
#define GET_TIME 2

#define READ_PORT 0x00
#define WRITE_PORT 0x01
#define PRINT_PORT 0x04
#define TICKER_PORT 0x05
#define MEMCPY_PORT 0x06

uint64_t sys_read(int fd, char * str, int length);
uint64_t sys_write(int fd, char * str, int length);
uint64_t sys_print(int fd, int length, int coor);
uint64_t sys_ticker(int fd, int length);
uint64_t sys_memcpy(uint32_t * dest, int length);

#endif