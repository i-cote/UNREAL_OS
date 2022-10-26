#ifndef SHELL_H
#define SHELL_H

#define ENTER '\x0d'
#define SPACE " "
#define BACKSPACE '\x08'
#define DELETE 127
#define MAX_READ 100

void shell();
void reading_command(char * str);
void waiting_command();
void printShellMenu();

#endif