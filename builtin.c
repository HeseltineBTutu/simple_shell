#include "main.h"
/**
 * built_in_exit - built-in function to exit the shell
 * @cmd: command line arguments
 */
void built_in_exit(char **cmd)
{
	long int status = 0;
	struct sigaction sa;

	if (strcmp("exit", cmd[0]) == 0)
	{
		if (cmd[1])
		{
			status = strtol(cmd[1], NULL, 10);
			if (status <= 0)
			{
				dprintf(STDERR_FILENO, "%s: exit: Illegal number: %s\n", arr[0], cmd[1]);
			}
		}
		free(cmd[0]);
		free(cmd);

		if (errno != 0)
		{
			exit(1);
		}
		else
		{
			memset(&sa, 0, sizeof(sa));
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = SA_RESTART;
			sigaction(SIGINT, &sa, NULL);
			/* Exit normally*/
			exit(status);
		}
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
