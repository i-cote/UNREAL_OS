
#include <stdioAPI.h>
#include <shell.h>
#include <string.h>
#include <syscallsAPI.h>
#include <tron.h>
#include <color.h>

#define NULL ((void*)0)

void shell(){
    printfColor("Welcome to the shell!\n", yellow);
    printfColor("Добро пожаловать в shell!", yellow);
    waiting_command();
}

void waiting_command(){
    while (1)
    {
        printfColor("\nType 'help' to see the available commands\n", yellow);
        char command_reader[MAX_READ];
        printfColor("\n%s", pink,"$ ");
        int count = 0;
        char current;
        while ((current = getChar()) != ENTER)
        {
            if (current == BACKSPACE || current == DELETE){
                if (count > 0){
                    command_reader[count] = '\0';
                    count--;
                    printfColor("%c", lime, current);
                }
            }
            else if(current != -1){
                command_reader[count] = current;
                count++;
                printfColor("%c", lime, current);
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

// Checks if command is a valid command and executes it
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
        printfColor("\n Invalid params\n", white);
    }
    
    else{
        printfColor("\n Command Not found\n", white);
    }
    
    
    return;
}
