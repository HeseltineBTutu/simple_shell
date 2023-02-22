#include "main.h"
/**
 * built_in_exit - exit shell
 * @cmd: array of string
 * Return: Always returns 0, to proceed with execution.
 */
void built_in_exit(char **cmd)
{
	int status;

	if (cmd == NULL || cmd[0] == NULL)
		return;

	if ((strcmp("exit", cmd[0]) == 0))
	{
		status = EXIT_SUCCESS;

		if (cmd[1])
			status = (int)strtol(cmd[1], NULL, 10);
		free(cmd[0]);
		free(cmd);
		exit(status);
	}
}

/**
 * built_in_env - print the current environment
 * @cmd: executable
 * Return: Always returns 0, to proceed with execution.
 */
void built_in_env(char *cmd)
{
	char **env = environ;

	if ((strcmp("env", cmd) == 0))
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
}
