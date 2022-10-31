#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#define COMMAND_NUMBER 10
#define MAX_PARAMS 4
#define MAX_LENGHT 20
#define ALIGNMENT 16
#define BYTE_GROUP 4
#define REGISTERS 16

typedef char args[MAX_PARAMS][MAX_LENGHT];

typedef struct
{
    char * name;
    void (*function) (args, int);
    int args;

}commands_style;


//static commands_style commands[COMMAND_NUMBER];

void inforeg(args argsVec, int argsNum);
void help(args argsVec, int argsNum);
void div_zero_exception_tester(args argsVec, int argsNum);
void invalid_opcode_exception_tester(args argsVec, int argsNum);
void tron_command(args argsVec, int argsNum);
void time(args argsVec, int argsNum);
void getContent(args argsVec, int argsNum);
void clear(args argsVec, int argsNum);
void biggie(args argsVec, int argsNum);
void smalls(args argsVec, int argsNum);

static commands_style commands[] = {
    {"biggie", biggie, 0},
    {"smalls", smalls, 0},
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
