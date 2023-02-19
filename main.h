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
#include <signal.h>
char *get_command(void);
char **getargs(char *command);
int execute_command(char **args);
extern char **environ;
int find(char *command, DIR *dir);
char *search(char *command);
char **arr;
#endif
