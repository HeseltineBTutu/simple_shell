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
	char *command_path;

	char *path = getenv("PATH");
	char *path_copy = malloc(strlen(path) + 1);
	if (path_copy == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	strcpy(path_copy, path);

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			command_path = malloc(strlen(command) + 1);
			if (command_path == NULL)
			{
				perror("malloc");
				free(path_copy);
				return (NULL);
			}
			strcpy(command_path, command);
			return (command_path);
		}
		else
		{
			free(path_copy);
			return (NULL);
		}
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = construct_full_path(dir, command);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		command_path = check_command_in_path(full_path);
		free(full_path);
		if (command_path != NULL)
		{
			free(path_copy);
			return (command_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);

}

/**
 * execute_shell_commands - Execute shell commands and control shell loop
 * @interactive_mode: Flag indicating interactive mode
 * Description:
 * This function manages the core functionality of the shell,
 * including handling user input, executing commands,
 * and controlling the shell loop.
*/
void execute_shell_commands(int interactive_mode)
{
	char *input;
	char *tokens[MAX_ARGUMENTS + 1];
	int token_count;
	int exit_status = EXIT_SUCCESS;

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
						exit(EXIT_FAILURE);
					}
				}
				execute_command(tokens);
				free_tokens(tokens, token_count);
			}
			free(input);
			if (!interactive_mode)
				break;
		}
	}
}

/**
 * main - The main function
 *
 * Return: Always 0
 */
int main(void)
{
	int interactive_mode;

	interactive_mode = isatty(STDIN_FILENO);
	execute_shell_commands(interactive_mode);
	return (0);
	}
