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

	char *full_path;

	if (tokens == NULL || tokens[0] == NULL)
	{
		return;
	}

	full_path = is_command_in_path(tokens[0]);

	if (full_path != NULL)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			free(full_path);
			return;
		}
		if (child_pid == 0)
		{
			execve(full_path, tokens, NULL);
			perror(full_path);
			free(full_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
		free(full_path);
	}
	else
	{
		perror(tokens[0]);
	}
}

/**
 * is_command_in_path - Check if a command exists in the directories listed
 *
 * @command: The command to check
 * Return: return command if it exits or NULL
 */
char  *is_command_in_path(const char *command)
{
	char *dir;
	char *full_path;
	char *path_copy;
	char *path;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			return strdup(command);
		}
		else
		{
			return (NULL);
		}
	}

	path = getenv("PATH");

	path_copy = strdup(path);

	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	dir = strtok(path_copy, ":");

	while (dir  != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
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
	int exit_status = EXIT_SUCCESS;

	int interactive_mode = isatty(STDIN_FILENO);
	
	signal(SIGINT, handle_sigint);

	while (1)
	{
		if (interactive_mode)
			display_prompt();

		input = read_input(tokens);

		if (input != NULL)
		{
			token_count = parse_input(input, tokens);

			if (token_count > 0)
			{
				if (strcmp(tokens[0], "exit") == 0)
				{
					if (token_count > 1)
					{
						exit_status = atoi(tokens[1]);
					}
					exit_shell(tokens, exit_status);
				}
				else if (strcmp(tokens[0], "env") == 0)
				{
					if (_env() == -1)
					{
						return (-1);
					}
				}

				execute_command(tokens);
				for (i = 0; i < token_count; i++)
				{
					free(tokens[i]);
					tokens[i] = NULL;
				}
			}
			free(input);

			if (!interactive_mode)
				break;
		}
	}
	return (0);
}
