#ifndef SHELL_H
#define SHELL_H

#define ENTER '\x0d'
#define MAX_READ 100

void shell();
void reading_command(int size, char * str);
void waiting_command();
void printShellMenu();

#endif