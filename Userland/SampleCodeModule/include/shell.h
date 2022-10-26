#ifndef SHELL_H
#define SHELL_H

#include <commands.h>

#define ENTER '\x0d'
#define SPACE " "
#define BACKSPACE '\x08'
#define DELETE 127
#define MAX_READ 100


void shell();
void reading_command(char commands[MAX_LENGHT_PARAMS],args argsVec, int argsNum);
void waiting_command();
void printShellMenu();

#endif