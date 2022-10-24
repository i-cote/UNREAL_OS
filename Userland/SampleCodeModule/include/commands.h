#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#define COMMAND_NUMBER 2

typedef struct commands_style
{
    char * name;
    void (*function) (void);

}commands_style;

static commands_style commands[COMMAND_NUMBER];

void inforeg();
void help();

uint64_t getRAX();
uint64_t getRBX();
uint64_t getRCX();
uint64_t getRDX();
uint64_t getRBP();
uint64_t getRSP();
uint64_t getRDI();
uint64_t getRSI();
uint64_t getR8();
uint64_t getR9();
uint64_t getR10();
uint64_t getR11();
uint64_t getR12();
uint64_t getR13();
uint64_t getR14();
uint64_t getR15();

// Get the registers from the CPU

#endif 