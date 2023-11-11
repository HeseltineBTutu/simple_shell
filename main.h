#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
void display_prompt(void);
char *read_input(char *tokens[]);
int parse_input(char **tokens);
#define MAX_ARGUMENTS 100
void execute_command(char **tokens);
char *is_command_in_path(const char *command);
#endif
