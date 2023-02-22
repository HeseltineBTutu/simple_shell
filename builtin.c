#include "main.h"
/**
 * built_in_exit - built-in function to exit the shell
 * @cmd: command line arguments
 */
void built_in_exit(char **cmd)
{
	long int status;
	char *endptr;

	if (strcmp("exit", cmd[0]) == 0)
	{
		if (cmd[1])
		{
			status = strtol(cmd[1], &endptr, 10);
			if (*endptr != '\0')
			{
				fprintf(stderr, "exit: %s: numeric argument required\n", cmd[1]);
				exit(EXIT_FAILURE);
			}
		}
		free(cmd[0]);
		free(cmd);
		exit(status);
	}
}
/**
 * built_in_env - print the current environment
 * @cmd: argument 0
 */
void built_in_env(char *cmd)
{
	char **env = environ;

	if (strcmp("env", cmd) == 0)
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
}
