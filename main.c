#include "main.h"
/**
 * main - Starts the shell program
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	char *prompt = "#cisfun$ ";
	char *command, **av;

	(void)argc;
	/*assign argv to global variable arr for error handling*/
	arr = argv;
	while (1)
	{
		write(STDOUT_FILENO, prompt, 9);
		fflush(stdout);

		command = get_command();
		av = getargs(command);
		execute_command(av);
		free(command);
		free(av);
	}
	return (0);
}
/**
 * get_command - Reads a command from stdin.
 *
 * Return: Pointer to the command string.
 */
char *get_command(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read = getline(&command, &len, stdin);

	if (read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			free(command);
			exit(0);
		}
		else
		{
			perror(arr[0]);
			exit(1);
		}
	}
	return (command);
}
/**
 * getargs - gets arguments
 * @command: passed command
 * Return: array of strings
 */
char **getargs(char *command)
{
	char **arguments = malloc(sizeof(char *) * 100);
	char *token, delim[] = " \t\r\n";
	int i = 0;

	/* Split the command line into separate arguments*/
	token = strtok(command, delim);
	while (token)
	{
		arguments[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	arguments[i] = NULL;
	return (arguments);
}
/**
 * execute_command - Execute a command in a childe process.
 * @args: array of command strings.
 * Return: 0 on success
 */
int execute_command(char **args)
{
	int status, w;
	pid_t pid;

	if (args[0] == NULL)
	{
		return (1);
	}
	if ((strcmp(args[0], "exit") == 0))
	{
		free(args[0]);
		free(args);
		exit(0);
	}
	/* Create a child process to execute the command */
	pid = fork();
	if (pid == 0)
	{
		/* In child process */
		if ((execve(args[0], args, environ) == -1))
		{
			perror(arr[0]);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror(arr[0]);
		exit(1);
	}
	else
	{
		/* In parent process, wait for child to finish */
		w = waitpid(pid, &status, 0);
		if (w == -1)
		{
			perror(arr[0]);
			exit(1);
		}
	}
	return (1);
}
