/*List of commands:
-help, muestra func disponibles
-info reg, imprime los valores actuales de los registros
-hora 
-memdir reciba como parámetro una dirección de memoria e imprima por pantalla los 32 bytes 
de memoria posteriores a la misma.
-big y smalls, Comando que permita agrandar o reducir el tamaño del texto de la pantalla*/

#include <stdioAPI.h>
#include <shell.h>
#include <getRegisters.h>

void shell(){
    printShellMenu();

    inforeg(); //llamado para testear nomas
}

void printShellMenu(){
    printf("Welcome to the shell!\n");
    printf("Type 'help' to see the available commands\n");
    printf("Command List:\n");
    printf("inforeg - Prints the registers\n");
    printf("time - Prints the current time\n");
    printf("tron - Lets you play tron\n");
    printf("zoomin - Lets you zoom in\n");
    printf("zoomout - Lets you zoom out\n");
    printf("help - Prints this menu\n");
    //Poner para recibir un comando
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