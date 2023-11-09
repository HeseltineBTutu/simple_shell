#include "main.h"

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	printf("($) ");
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
	char *input;
	char *tokens[MAX_ARGUMENTS + 1];
	int token_count;
	int i;

	while (1)
	{
		display_prompt();
		input = read_input();

		if (input != NULL)
		{
			token_count = parse_input(tokens);
			if (token_count > 0)
			{
				execute_command(tokens);
				for (i = 0; i < token_count; i++)
					free(tokens[i]);
			}
			free(input);
		}
	}
	return (0);
}
