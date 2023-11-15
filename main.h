#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
void display_prompt(void);
void execute_shell_commands(int interactive_mode);
char *read_input(char *tokens[]);
int tokenize_input(const char *input, char **tokens);
int parse_input(const char *input, char **tokens);
#define MAX_ARGUMENTS 100
void execute_command(char **tokens);
char *construct_full_path(const char *dir, const char *command);
char *check_command_in_path(const char *full_path);
char *is_command_in_path(const char *command);
void exit_shell(char **tokens, int status);
extern char **environ;
int _env(void);
void handle_sigint(int sig);
ssize_t getline_custom(char **lineptr, size_t *n, FILE *stream);
void free_tokens(char **tokens, int token_count);
#define INITIAL_BUFFER_SIZE 128
#define BUFFER_INCREMENT 128
#endif
