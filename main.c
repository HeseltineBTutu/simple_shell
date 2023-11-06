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
char *read_command(void)
{
	char *command = NULL;
	size_t command_size = 0;
	ssize_t bytes_read;

	bytes_read = getline(&command, &command_size, stdin);

	if (bytes_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
	}
	if (bytes_read > 0 && command[bytes_read - 1] == '\n')
		command[bytes_read - 1] = '\0';

	return (command);
}

/**
 * execute_command - Execute the command
 *
 * @command: The command to execute
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	char **args;
	char num_args = 2;

	args = malloc(sizeof(char *) * num_args);

	if (args == NULL)
	{
		perror("malloc");
		return;
	}
	args[0] = command;
	args[1] = NULL;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		free(args);
		return;
	}
	if (child_pid == 0)
	{
		execve(command, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
	free(args);
}

/**
 * main - The main function
 *
 * Return: Always 0
 */
int main(void)
{
	char *command;

	while (1)
	{
		display_prompt();
		command = read_command();
		execute_command(command);
		free(command);
	}
	return (0);
}
