#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
char *get_command(void);
void execute_command(char *command);
extern char **environ;
char **arr;
#define BUFSIZE 1024
#endif
