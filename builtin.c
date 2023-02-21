#include "main.h"

/**
 * built_in_exit - exit shell
 *
 * Return: Always returns 0, to proceed with execution.
 */
int built_in_exit(void)
{
	 _exit(0);
}

/**
 * built_in_env - print the current environment
 *
 * Return: Always returns 0, to proceed with execution.
 */
int built_in_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
/**
 * execute_built_in - executes env and exit
 * @command: array of strings
 */
void execute_built_in(char **command)
{
	if (strcmp(command[0], "exit") == 0)
	{
		free(command[0]);
		free(command);
		built_in_exit();
	}
	if (strncmp(command[0], "env", 3) == 0)
	{
		built_in_env();
	}
}
