#include "main.h"

/**
 * built_in_exit - exit shell
 *
 * Return: Always returns 0, to proceed with execution.
 */
int built_in_exit(void)
{
	exit(EXIT_SUCCESS);
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
