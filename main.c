#include "main.h"

int main(int ac, char **argv)
{
	char *prompt;
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t bytes_read;
	char **command_argv;
	(void)ac;
	(void)argv;

	prompt = "(MiniShell)$ ";
	while (1)
	{
		printf("%s", prompt);
		bytes_read = getline(&lineptr, &n, stdin);
		if (bytes_read == -1)
		{
			printf("Exiting shell\n");
			if (lineptr != NULL)
			{
				free(lineptr);
			}
			return (-1);
		}
		command_argv = parse_command(lineptr);
		if (command_argv == NULL)
		{
			printf("Memory Allocation Failure\n");
			free(lineptr);
			return (-1);
		}
		printf("%s\n", lineptr);
	}
	if (lineptr != NULL)
	{
		free(lineptr);
	}
return (0);
}

/**
 * parse_command - Parse a command string into an argument vector (argv).
 * @lineptr: The input string to be parsed.
 *
 * Return: An array of strings representing the command arguments (argv).
 *         The array should be terminated with a NULL pointer.
 *         NULL is returned in case of a memory allocation failure.
 */
char **parse_command(char *lineptr)
{
	char *lineptr_copy;
	char *token;
	char **argv;
	int i;
	char *tokens[MAX_NUM_TOKENS];

	int num_tokens = 0;

	lineptr_copy = strdup(lineptr);
	if (lineptr_copy == NULL)
	{
		printf("Memory allocation Error");
		free(lineptr_copy);
		return (NULL);
	}
	token =  strtok(lineptr_copy, " ");
	while (token != NULL && num_tokens < MAX_NUM_TOKENS)
	{
		tokens[num_tokens++] = token;
		token = strtok(NULL, " ");
	}
	argv = (char **)malloc((num_tokens + 1) * sizeof(char *));
	if (argv == NULL)
	{
		printf("Memory allocation Error");
		free(lineptr_copy);
		return (NULL);
	}
	for (i = 0; i < num_tokens; i++)
	{
		argv[i] = strdup(tokens[i]);
	}
	argv[i] = NULL;
	free(lineptr_copy);
	return (argv);
}
