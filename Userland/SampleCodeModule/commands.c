
#include <commands.h>
#include <shell.h>


void help(){
    printf("\n");
    printf("Command List:\n");
    printf("inforeg - Prints the registers\n");
    printf("divzero - Tests div zero exception\n");
    printf("invopcode - TEsts invalid opcode exception\n");
    printf("time - Prints the current time\n");
    printf("tron - Lets you play tron\n");
    printf("biggie - Lets you zoom in\n");
    printf("smalls - Lets you zoom out\n");
    printf("help - Prints this menu\n");
}

void inforeg(){
    //Poner para imprimir los registros
    printf("\n");
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

void div_zero_exception_tester(){
    int j=1,i=0;
    j=j/i;
}

void invalid_opcode_exception_tester(){
    invalidOpcodeTester();
}

void tron_command(){
    tron();
}


void time(){
    printf("\n");
    while(1){
        if(getStatusRegA()!=0x80){
            printf("The time is: %d:%x:%x\n",calculateHours() ,getMinutes(),getSeconds());
            return;
        }
    }
}


int calculateHours(){
    int hours;
    switch (getHours()){
        case 0x00000017:
            hours=20;
            break;  
        case 0x00000016:
            hours=19;
            break;
        case 0x00000015:
            hours=18;
            break;
        case 0x00000014:
            hours=17;
            break;
        case 0x00000013:
            hours=16;
            break;
        case 0x00000012:
            hours=15;
            break;
        case 0x00000011:
            hours=14;
            break;
        case 0x00000010:
            hours=13;
            break;
        case 0x0000000F:
            hours=12;
            break;
        case 0x0000000E:
            hours=11;
            break;
        case 0x0000000D:
            hours=10;
            break;
        case 0x0000000C:
            hours=9;
            break;
        case 0x0000000B:
            hours=8;
            break;
        case 0x0000000A:
            hours=7;
            break;
        case 0x00000009:
            hours=6;
            break;
        case 0x00000008:
            hours=5;
            break;
        case 0x00000007:
            hours=4;
            break;
        case 0x06:
            hours=3;
            break;
        case 0x00000005:
            hours=2;
            break;
        case 0x00000004:
            hours=1;
            break;
        case 0x00000003:
            hours=0;
            break;
        case 0x00000002:
            hours=23;
            break;
        case 0x00000001:
            hours=22;
            break;
        case 0x00000000:
            hours=21;
            break;
        default:
            break;
    }
   
    return hours;
}

