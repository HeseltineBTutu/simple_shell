#include "main.h"
/**
 * built_in_exit - built-in function to exit the shell
 * @av: command line arguments
 * Return: 0 on success, or an error code if there was an error
 */
int built_in_exit(char **av)
{
	int status = 0;

	if (av[0] == NULL || strcmp(av[0], "exit") != 0)
		return (0);
	if (av[1] != NULL)
	{
		status = strtol(av[1], NULL, 10);
		if (status <= 0)
		{
			fprintf(stderr, "%s: exit: %d: Illegal number: %s\n", arr[0], 1, av[1]);
		}
	}
	free(av);
	exit(status);
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
