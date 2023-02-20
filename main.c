#include "main.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	ssize_t read;
	size_t len = 0;
	char *prompt = "#cisfun$ ";
	char *command = NULL;
	char **args;

	(void) argc;
	arr = argv;
	while (1)
	{
		if ((isatty(STDIN_FILENO)))
			write(STDOUT_FILENO, prompt, 9);
		read = getline(&command, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				free(command);
				return (0);
			}
			else
				return (1);
		}
		args = getargs(command);
		execute(args);
		free(args);
	}
	return (0);
}
/**
 * getargs - tokenizes command into arguments
 * @command: command to be tokenized
 * Return: tokenized string or NULL on error
 */
char **getargs(char *command)
{
	int i = 0;
	char delim[] = " \t\r\n";
	char *token;
	char **av = malloc(sizeof(char *) * 100);

	if (av == NULL)
		return (0);
	token = strtok(command, delim);
	while (token)
	{
		av[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	av[i] = NULL;
	return (av);
}
/**
 * execute - executes a command
 * @av: command line arguments
 * Return: 0 on success -1 on failure
 */
int execute(char **av)
{
	pid_t pid;
	int status, w;

	if (av[0] == NULL)
	{
		free(av[0]);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror(arr[0]);
		return (-1);
	}
	if (pid == 0)
	{
		if ((execve(av[0], av, NULL) == -1))
		{
			perror(arr[0]);
			return (-1);
		}
	}
	else
	{
		w = wait(&status);
		if (w == -1)
		{
			perror(arr[0]);
			return (-1);
		}
	}
	return (0);
}
