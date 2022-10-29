#include <stdint.h>
#include <commands.h>
#include <shell.h>
#include <stdioAPI.h>
#include <tron.h>
#include <syscallsAPI.h>


void help(args argsVec, int argsNum){
    printf("\n");
    printf("Command List:\n");
    printf("inforeg - Prints the registersof screenshot taken previously\n");
    printf("divzero - Tests div zero exception\n");
    printf("invopcode - TEsts invalid opcode exception\n");
    printf("time - Prints the current time\n");
    printf("clear - Clears the screen\n");
    printf("tron - Lets you play tron\n");
    printf("biggie - Lets you zoom in\n");
    printf("smalls - Lets you zoom out\n");
    printf("getContent - Print the next 32 bytes to the memory address you pass as an argument \n");
    printf("help - Prints this menu\n");
}

void inforeg(args argsVec, int argsNum){
    uint64_t registerVector[REGISTERS] = {0};
    sys_memcpy_asm(registerVector,REGISTERS);

    //Poner para imprimir los registros
    printf("\n");
    printf("Registers:\n");
    printf("RAX: 0x%x\n", registerVector[0]);
    printf("RBX: 0x%x\n", registerVector[1]);
    printf("RCX: 0x%x\n", registerVector[2]);
    printf("RDX: 0x%x\n", registerVector[3]);
    printf("RBP: 0x%x\n", registerVector[4]);
    printf("RSP: 0x%x\n", registerVector[5]);
    printf("RDI: 0x%x\n", registerVector[6]);
    printf("RSI: 0x%x\n", registerVector[7]);
    printf("R8: 0x%x\n", registerVector[8]);
    printf("R9: 0x%x\n", registerVector[9]);
    printf("R10: 0x%x\n", registerVector[10]);
    printf("R11: 0x%x\n", registerVector[11]);
    printf("R12: 0x%x\n", registerVector[12]);
    printf("R13: 0x%x\n", registerVector[13]);
    printf("R14: 0x%x\n", registerVector[14]);
    printf("R15: 0x%x\n", registerVector[15]);
    
}

void biggie(args argsVec, int argsNum)
{
	printf("\nAgrandir\n");
}

void smalls(args argsVec, int argsNum)
{
	printf("\nRapetissir\n");
}

void div_zero_exception_tester(args argsVec, int argsNum){
    int j=1,i=0;
    j=j/i;
}

void invalid_opcode_exception_tester(args argsVec, int argsNum){
    invalidOpcodeTester();
}

void tron_command(args argsVec, int argsNum){
    tron();
}

void clear(args argsVec, int argsNum){
    clearScreen();
}

void getContent(args argsVec, int argsNum){
    char * address = (char *) argsVec[0];
    uintptr_t realAddress = (uintptr_t)hex2int(address);
    if (realAddress % ALIGNMENT != 0){
        realAddress -= (realAddress % ALIGNMENT);
    }
    uint8_t * targetAddress = (uint8_t *) realAddress;

    printf("\n");
    for(int i = 0; i < 8; i++){
        printf("0x%x | %x %x %x %x |", targetAddress, targetAddress[BYTE_GROUP], targetAddress[BYTE_GROUP + 1],
        targetAddress[BYTE_GROUP + 2], targetAddress[BYTE_GROUP + 3]);
        printf(" %c %c %c %c", targetAddress[BYTE_GROUP], targetAddress[BYTE_GROUP + 1], targetAddress[BYTE_GROUP + 2], targetAddress[BYTE_GROUP + 3]);
        printf("\n");
        targetAddress += 4;
    }
    
}

void time(args argsVec, int argsNum){
    printf("\n");
    while(1){
        if(getStatusRegA()!=0x80){
            printf("The time is: %d:%x:%x\n",calculateHours() ,getMinutes(),getSeconds());
            return;
        }
    }
}


int calculateHours(){

	int dec = getHours() & 240;
	dec = dec >> 4;
	int units = getHours() & 15;
	return ((dec * 10 + units)+21)%24;

}

