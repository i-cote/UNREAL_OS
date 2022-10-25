/*List of commands:
-help, muestra func disponibles
-info reg, imprime los valores actuales de los registros
-hora 
-memdir reciba como parámetro una dirección de memoria e imprima por pantalla los 32 bytes 
de memoria posteriores a la misma.
-big y smalls, Comando que permita agrandar o reducir el tamaño del texto de la pantalla*/

#include <stdioAPI.h>
#include <shell.h>
#include <commands.h>
#include <string.h>
#include <syscallsAPI.h>
#include <tron.h>



void shell(){
    printShellMenu();
    tron();
    waiting_command();
}

void waiting_command(){

    while (1)
    {
        char command_reader[MAX_READ];
        printf("\n%s", "$ ");
        int count = 0;
        char current;
        while ((current = getChar()) != ENTER)
        {
            if(current != -1){
                command_reader[count] = current;
                count++;
                printf("%c",current);
            }
        }
        
        //Preparing the command for read
        //printf("no se rompe");
        //printf("%d",count);
        char toRead[count+1];
        for (int i = 0; i < count; i++)
        {
            toRead[i] = command_reader[i];
        }
        toRead[count]=0;
        
        reading_command(count, toRead);
    }
}

void reading_command(int size, char * str){

    int found = 0;
    int to_execute;
    for (int i = 0; i < COMMAND_NUMBER && !found; i++){
        if (0==strcmp(commands[i].name, str)){
            found = 1;
            to_execute = i;
        }
        
    }

    if(found){
        commands[to_execute].function();
    }
    else{
        printf("\n Command Not found");
    }
    
    return;
}

void printShellMenu(){
    printf("Welcome to the shell!\n");
    printf("Type 'help' to see the available commands\n");
}
