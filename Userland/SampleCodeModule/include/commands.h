#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#define COMMAND_NUMBER 8
#define MAX_PARAMS 4
#define MAX_LENGHT_PARAMS 20
#define ALIGNMENT 16
#define BYTE_GROUP 4
#define REGISTERS 16

typedef struct commands_style
{
    char * name;
    void (*function) (args);
    int args;

}commands_style;

typedef char args[MAX_PARAMS][MAX_LENGHT_PARAMS] ;

//static commands_style commands[COMMAND_NUMBER];

void inforeg(args argsVec);
void help(args argsVec);
void div_zero_exception_tester(args argsVec);
void invalid_opcode_exception_tester(args argsVec);
void tron_command(args argsVec);
void time(args argsVec);
void getContent(args argsVec);
void clear(args argsVec);

static commands_style commands[] = {
    {"inforeg", inforeg, 0},
    {"help", help, 0},
    {"divzero", div_zero_exception_tester, 0},
    {"invopcode",invalid_opcode_exception_tester, 0},
    {"time",time, 0},
    {"clear", clear, 0},
    {"tron",tron_command, 0},
    {"getContent", getContent, 1}
};

void invalidOpcodeTester();

uint64_t getStatusRegA();
uint64_t getSeconds();
uint64_t getMinutes();
uint64_t getHours();
int uint_64toint(uint64_t number);

int calculateHours();

#endif 