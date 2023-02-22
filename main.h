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
#define BUFSIZE 1024
char **getargs(char *command);
int execute(char **args);
char *get_path(void);
char *find_command(char *command);
void built_in_exit(char **av);
void built_in_env(char *cmd);
extern char **environ;
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
char **arr;
#endif
