#include "main.h"
/**
 * built_in_exit - built-in function to exit the shell
 * @cmd: command line arguments
 * Return: 1 on execution 0 otherwise
 */
int built_in_exit(char **cmd)
{
	long int status = 0;

	if (strcmp("exit", cmd[0]) == 0)
	{
		if (cmd[1])
		{
			status = strtol(cmd[1], NULL, 10);
			if (status <= 0)
			{
				return (0);
			}
		}
		free(cmd[0]);
		free(cmd);
		_exit(status);
	}
	return (1);
}
/**
 * built_in_env - print the current environment
 * @cmd: argument 0
 * Return: 1 on execution, 0 if not
 */
int built_in_env(char *cmd)
{
	char **env = environ;

	if (!env)
		return (0);
	if (strcmp("env", cmd) == 0)
	{
		while (*env)
		{
			printf("%p\n", (const void *)*env);
			env++;
		}
	}
	return (1);
}
