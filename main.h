#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
#endif
