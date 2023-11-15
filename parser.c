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
	char *duplicate_input;


	bytes_read = getline(&input, &input_size, stdin);

	if (input == NULL)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}

	if (bytes_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			free(input);
			exit(EXIT_SUCCESS);
		}
	}

	if (bytes_read == 0)
	{
		free(input);
		return (NULL);
	}
	if (bytes_read > 0 && input[bytes_read - 1] == '\n')
		input[bytes_read - 1] = '\0';

	duplicate_input = malloc(bytes_read);
	if (duplicate_input == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(duplicate_input, input);
	free(input);

	tokens[0] = duplicate_input;

	return (duplicate_input);
}

/**
 * tokenize_input - Tokenize the input into an array of tokens
 * @input: The input to be tokenized
 * @tokens: The array to store the parsed tokens
 * Return: The number of tokens parsed, or -1 on error
 */
int tokenize_input(const char *input, char **tokens)
{
	char *token;
	int i;
	char *delimiter;
	char *input_copy;

	int token_count = 0;

	input_copy = malloc(strlen(input) + 1);

	if (input_copy == NULL)
	{
		perror("malloc");
		return (-1);
	}
	strcpy(input_copy, input);
	delimiter = " \t";
	token = strtok(input_copy, delimiter);

	while (token != NULL && token_count < MAX_ARGUMENTS)
	{
		tokens[token_count] = malloc(strlen(token) + 1);
		if (tokens[token_count] == NULL)
		{
			perror("malloc");
			free(input_copy);
			for (i = 0; i < token_count; i++)
			{
				free(tokens[i]);
			}
			return (-1);
		}
		strcpy(tokens[token_count], token);
		token_count++;
		token = strtok(NULL, delimiter);
	}
	tokens[token_count] = NULL;

	free(input_copy);
	return (token_count);
}

/**
 * parse_input - Parse the input into tokens
 *
 * @input: The input to be parsed
 * @tokens: The array to store the parsed tokens
 *
 * Return: The number of tokens parsed
 */
int parse_input(const char *input, char **tokens)
{
	int token_count;

	if (tokens == NULL || tokens[0] == NULL || tokens[0][0] == '\0')
	{
		return (0);
	}
	token_count = tokenize_input(input, tokens);
	if (token_count == -1)
	{
		return (-1);
	}
	if (token_count == MAX_ARGUMENTS && strtok(NULL, " \t") != NULL)
	{
		return (-1);
	}
	return (token_count);
}
