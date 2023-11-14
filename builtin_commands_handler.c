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

	for (i = 0; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
		tokens[i] = NULL;
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

/**
 * handle_built_in_commands - Handle built-in commands like "exit" and "env"
 *
 * @tokens: The tokens containing the command and arguments
 *
 * Return: 1 if not a built-in command, 0 on successful handling of built-in command,
 *         -1 on failure
 */
int handle_built_in_commands(char **tokens)
{
	int exit_status;

	if (strcmp(tokens[0], "exit") == 0)
	{
		exit_status = (tokens[1] != NULL) ? atoi(tokens[1]) : EXIT_SUCCESS;
		exit_shell(tokens, exit_status);
	}
	else if (strcmp(tokens[0], "env") == 0)
	{
		return ((_env() == -1) ? -1 : 0);
	}
	return (-1);
}
