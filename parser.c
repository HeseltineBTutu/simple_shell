#include "main.h"

/**
 * read_input - Read input from the user
 *
 * Return: The input entere by the user
 */
char *read_input(char *tokens[])
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

	tokens[0] = input;

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
	char *input_copy;

	input_copy = strdup(tokens[0]);
	if (input_copy == NULL)
	{
		perror("strdup");
		return (-1);
	}

	token = strtok(input_copy, " \t");

	while (token != NULL && token_count < MAX_ARGUMENTS)
	{
		tokens[token_count] = strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("strdup");
			free(input_copy);
			return (-1);
		}
		token_count++;
		token = strtok(NULL, " \t");
	}
	free(input_copy);
	tokens[token_count] = NULL;

	return (token_count);
}
