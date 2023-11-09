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

	if (is_command_in_path(tokens[0]))
	{
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
	else
	{
		printf("Command not found: %s\n", tokens[0]);
	}
}

/**
 * is_command_in_path - Check if a command exists in the directories listed
 *
 * @command: The command to check
 * Return: 1 if the command exists, 0 if not
 */
int is_command_in_path(const char *command)
{
	char *dir;
	char *full_path;

	char *path = getenv("PATH");
	char *path_copy = strdup(path);

	if (path_copy == NULL)
	{
		perror("strdup");
		return (0);
	}
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (0);
		}
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(full_path);
			free(path_copy);
			return (1);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (0);
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
