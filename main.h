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
void built_in_env(char *cmd);
int built_in_exit(char **av);
int built_in_exit(void);
int built_in_env(void);
extern char **environ;
void execute_built_in(char **command);
ssize_t get_line(char **buffer, size_t *buffer_size);
char **arr;
#endif
