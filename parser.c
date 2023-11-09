#include "main.h"

/**
 * read_input - Read input from the user
 *
 * Return: The input entere by the user
 */
char *read_input(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t bytes_read;

	bytes_read = getline(&input, &input_size, stdin);

	if (bytes_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
	}
	if (bytes_read > 0 && input[bytes_read - 1] == '\n')
		input[bytes_read - 1] = '\0';

	return (input);
}

/**
 * parse_input - Parse the input into tokens
 *
 * @input: The input to be parsed
 * @tokens: The array to store the parsed tokens
 *
 * Return: The number of tokens parsed
 */
int parse_input(char **tokens)
{
	char *token;
	int token_count = 0;
	int i;

	token = strtok(tokens[0], " \t");

	while (token != NULL && token_count < MAX_ARGUMENTS)
	{
		tokens[token_count] = strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("strdup");
			for (i = 0; i < token_count; i++)
			{
				free(tokens[i]);
			}
			return (-1);
		}
		token = strtok(NULL, " \t");
		token_count++;
	}
	tokens[token_count] = NULL;
	return (token_count);
}
