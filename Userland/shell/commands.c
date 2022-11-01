#include <stdint.h>
#include <shell.h>
#include <stdioAPI.h>
#include <tron.h>
#include <syscallsAPI.h>
#include <color.h>

// Prints on screen the help menu
void help(args argsVec, int argsNum){
    printfColor("\n", white);
    printfColor("Command List:\n", white);
    printfColor(" *inforeg -> Prints the registers of screenshot taken previously\n",white);
    printfColor(" *divzero -> Tests div zero exception\n",white);
    printfColor(" *invopcode -> Tests invalid opcode exception\n",white);
    printfColor(" *time -> Prints the current time\n",white);
    printfColor(" *clear -> Clears the screen\n",white);
    printfColor(" *tron -> Lets you play tron\n",white);
    printfColor(" *biggie -> Lets you zoom in\n",white);
    printfColor(" *smalls -> Lets you zoom out\n",white);
    printfColor(" *getContent -> Print the next 32 bytes to the memory address you pass as an argument \n",white);
    printfColor(" *help -> Prints this menu\n",white);
}

// Prints on screen the registers of the screenshot taken previously
void inforeg(args argsVec, int argsNum){
    uint64_t registerVector[REGISTERS] = {0};
    sys_memcpy_asm(registerVector,REGISTERS);

    printfColor("\n", white);
    printfColor("Registers:\n", white);
    printfColor("RAX: 0x%x\n", white,registerVector[15]);
    printfColor("RBX: 0x%x\n", white,registerVector[14]);
    printfColor("RCX: 0x%x\n", white,registerVector[13]);
    printfColor("RDX: 0x%x\n", white,registerVector[12]);
    printfColor("RBP: 0x%x\n", white,registerVector[11]);
    printfColor("RSP: 0x%x\n", white,registerVector[10]);
    printfColor("RDI: 0x%x\n", white,registerVector[9]);
    printfColor("RSI: 0x%x\n", white,registerVector[8]);
    printfColor("R8: 0x%x\n", white,registerVector[7]);
    printfColor("R9: 0x%x\n", white,registerVector[6]);
    printfColor("R10: 0x%x\n", white,registerVector[5]);
    printfColor("R11: 0x%x\n", white,registerVector[4]);
    printfColor("R12: 0x%x\n", white,registerVector[3]);
    printfColor("R13: 0x%x\n", white,registerVector[2]);
    printfColor("R14: 0x%x\n", white,registerVector[1]);
    printfColor("R15: 0x%x\n", white,registerVector[0]);
    
}

static uint32_t font_size = 16;

// Increases the font size
void biggie(args argsVec, int argsNum)
{
	if(font_size==8)
		font_size = 16;
	else if(font_size==16)
		font_size =32;
	printfColor("\x1b\x5bsetFontSize %d",white,font_size);
}

// Decreases the font size
void smalls(args argsVec, int argsNum)
{
	if(font_size==32)
		font_size = 16;
	else if (font_size==16)
		font_size = 8;
	printfColor("\x1b\x5bsetFontSize %d",white,font_size);
}

// Function to test div zero exception
void div_zero_exception_tester(args argsVec, int argsNum){
    int j=1,i=0;
    j=j/i;
}

// Function to test invalid opcode exception
void invalid_opcode_exception_tester(args argsVec, int argsNum){
    invalidOpcodeTester();
}

// Function to run tron
void tron_command(args argsVec, int argsNum){
    tron();
}

// Clears shell
void clear(args argsVec, int argsNum){
    clearScreen();
}

// Prints the 32 bytes of memory starting at the address passed as an argument
void getContent(args argsVec, int argsNum){
    char * address = (char *) argsVec[0];
    uintptr_t realAddress = (uintptr_t)hex2int(address);
    if (realAddress % ALIGNMENT != 0){
        realAddress -= (realAddress % ALIGNMENT);
    }
    uint8_t * targetAddress = (uint8_t *) realAddress;

    printfColor("\n",white);
    for(int i = 0; i < 8; i++){
        printfColor("0x%x | %x %x %x %x |", white,targetAddress, targetAddress[BYTE_GROUP], targetAddress[BYTE_GROUP + 1],
        targetAddress[BYTE_GROUP + 2], targetAddress[BYTE_GROUP + 3]);
        printfColor(" %c %c %c %c", white,targetAddress[BYTE_GROUP], targetAddress[BYTE_GROUP + 1], targetAddress[BYTE_GROUP + 2], targetAddress[BYTE_GROUP + 3]);
        printfColor("\n",white);
        targetAddress += 4;
    }
    
}

// Prints the current time
void time(args argsVec, int argsNum){
    printfColor("\n",white);
    while(1){
        if(getStatusRegA()!=0x80){
            printfColor("The time is: %d:%x:%x\n",white,calculateHours() ,getMinutes(),getSeconds());
            return;
        }
    }
}

// Changes hour format from UTC to local time (UTC-3)
int calculateHours(){

	int dec = getHours() & 240;
	dec = dec >> 4;
	int units = getHours() & 15;
	return ((dec * 10 + units)+21)%24;

}

