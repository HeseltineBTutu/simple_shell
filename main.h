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
char **getargs(char *command);
int execute(char **args);
char *get_path(void);
char *find_command(char *command, char *path);
extern char **environ;
char **arr;
#endif
