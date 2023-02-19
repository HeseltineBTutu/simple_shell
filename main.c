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
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 9);

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
			free(command);
			exit(0);
		}
		else
		{
			perror(arr[0]);
			exit(1);													}
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
	char **arguments = malloc(sizeof(char *) * strlen(command));
	char *token, delim[] = " \t\r\n";
	int i = 0;

	if (!arguments)
		exit(1);
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
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args)
{
	int status, w;
	pid_t pid;
	char *cmd;

	if (args[0] == NULL)
	{
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		cmd = search(args[0]);
		if ((execve(cmd, args, environ) == -1))
		{
			perror(arr[0]);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror(arr[0]);
		return (-1);
	}
	else
	{
		/* In parent process, wait for child to finish */
		w = waitpid(pid, &status, 0);
		if (w == -1)
		{
			perror(arr[0]);
			return (-1);
																	}
	}
	return (0);
}
