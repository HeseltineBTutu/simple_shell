#include "main.h"

/**
 * exit_shell - Exit the shell
 *
 * This function frees allocated memory and exits the program.
 *
 * @tokens: The array of parsed tokens
 */
void exit_shell(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
	}
	free(tokens[i]);

	exit(EXIT_SUCCESS);
}
