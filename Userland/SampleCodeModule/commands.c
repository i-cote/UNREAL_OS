
#include <commands.h>
#include <shell.h>

static commands_style commands[] = {
    {"inforeg", inforeg},
    {"help", help}
};

void help(){
    printf("Command List:\n");
    printf("inforeg - Prints the registers\n");
    printf("time - Prints the current time\n");
    printf("tron - Lets you play tron\n");
    printf("zoomin - Lets you zoom in\n");
    printf("zoomout - Lets you zoom out\n");
    printf("help - Prints this menu\n");
}

void inforeg(){
    //Poner para imprimir los registros
    printf("Registers:\n");
    printf("RAX: 0x%x\n", getRAX());
    printf("RBX: 0x%x\n", getRBX());
    printf("RCX: 0x%x\n", getRCX());
    printf("RDX: 0x%x\n", getRDX());
    printf("RBP: 0x%x\n", getRBP());
    printf("RSP: 0x%x\n", getRSP());
    printf("RDI: 0x%x\n", getRDI());
    printf("RSI: 0x%x\n", getRSI());
    printf("R8: 0x%x\n", getR8());
    printf("R9: 0x%x\n", getR9());
    printf("R10: 0x%x\n", getR10());
    printf("R11: 0x%x\n", getR11());
    printf("R12: 0x%x\n", getR12());
    printf("R13: 0x%x\n", getR13());
    printf("R14: 0x%x\n", getR14());
    printf("R15: 0x%x\n", getR15());
}