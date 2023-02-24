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
		if (!cmd[1])
			status = 0;
		free(cmd[0]);
		free(cmd);
		exit(status);
	}
	return (1);
}
