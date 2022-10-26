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
            if (current == BACKSPACE || current == DELETE){
                if (count > 0){
                    command_reader[count] = '\0';
                    count--;
                    printf("%c", current);
                }
            }
            else if(current != -1){
                command_reader[count] = current;
                count++;
                printf("%c", current);
            }
        }
        //Preparing the command for read
        //First i get the line 
        char line[count+1];
        for (int i = 0; i < count; i++)
        {
            line[i] = command_reader[i];
            
        }
        line[count]='\0';
        //Now i use strtok for delete the spaces
        char * toRead = my_strtok(line, SPACE);
        
        reading_command(toRead);
    }
}

void reading_command(char * str){

    int found = 0;
    int to_execute;
    for (int i = 0; i < COMMAND_NUMBER && !found; i++){
        if (!(strcmp(commands[i].name, str))){
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
