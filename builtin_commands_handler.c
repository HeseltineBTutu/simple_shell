#include "main.h"

/**
 * exit_shell - Exit the shell
 *
 * This function frees allocated memory and exits the program.
 *
 * @tokens: The array of parsed tokens
 */
void exit_shell(char **tokens, int status)
{
	int i;

	if (tokens != NULL)
	{
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
	}
	if (status == -1)
	{
		if (errno == ENOENT || errno == EACCES)
		{
			status = EXIT_FAILURE;
		}
		else
		{
			status = EXIT_SUCCESS;
		}
	}
	exit(status);
}

/**
 * _env - Print the current environment
 *
 * Description: This function prints the current environment.
 *
 * Return: Always returns 0 to indicate success.
 */
int _env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
