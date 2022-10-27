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

#define NULL ((void*)0)

void shell(){
    printf("Welcome to the shell!");
    waiting_command();
}

void waiting_command(){
    while (1)
    {
        printf("\nType 'help' to see the available commands\n");
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

        char command[MAX_LENGHT] = {0};
        //Consume the command
        strcpy(command, toRead);
        toRead = my_strtok (NULL, SPACE);

        args tokens;
        
        //Now i consume the args
        int index = 0;
        while (toRead != NULL)
        {   
            strcpy(tokens[index++], toRead);
            toRead = my_strtok (NULL, SPACE);
        }

        reading_command(command, tokens, index);
    }
    
}

void reading_command(char command[MAX_LENGHT], args argsVec, int argsNum){

    int found = 0;
    int args_check = 0;
    int args = 0;
    int to_execute;
    for (int i = 0; i < COMMAND_NUMBER && !found; i++){
        if (!(strcmp(commands[i].name, command))){
            found = 1;
            //Checking if the amount of args is correct
           if(commands[i].args == argsNum){
                args_check = 1;
                args = commands[i].args;
                to_execute = i;
            }
        }
        
    }

    if(found && args_check){
        commands[to_execute].function(argsVec, args);
    }
    else if (found && !args_check)
    {
        printf("\n Invalid params\n");
    }
    
    else{
        printf("\n Command Not found\n");
    }
    
    
    return;
}
