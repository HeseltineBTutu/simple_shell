#include "main.h"

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	printf("($) ");
}

/**
 * read_command - Read a command from the user
 *
 * Return: The command entered by the user
 */
char **read_command(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t bytes_read;
	char **tokens;
	char *token;
	int i;

	int token_count = 0;

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

	tokens = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));

	if (tokens == NULL)
	{
		perror("malloc");
		free(input);
		return (NULL);
	}

	token = strtok(input, " \t");

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
			free(tokens);
			free(input);
			return (NULL);
		}

		token = strtok(NULL, " \t");
		token_count++;
	}
	tokens[token_count] = NULL;
	free(input);
	return (tokens);
}

/**
 * execute_command - Execute the command
 *
 * @command: The command to execute
 */
void execute_command(char **tokens)
{
	pid_t child_pid;
	int status;

	if (tokens == NULL || tokens[0] == NULL)
	{
		return;
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	if (child_pid == 0)
	{
		execve(tokens[0], tokens, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - The main function
 *
 * Return: Always 0
 */
int main(void)
{
	char **tokens;
	int i;

	while (1)
	{
		display_prompt();
		tokens = read_command();

		if (tokens != NULL)
		{
			execute_command(tokens);
			for (i = 0; tokens[i] != NULL; i++)
				free(tokens[i]);
			free(tokens);
		}
	}
	return (0);
}
