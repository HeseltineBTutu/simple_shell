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
		printf("%s", prompt);
		if (getline(&command, &len, stdin) == -1) break;
		execute(getargs(command));
		free(command);
	return (0);
	}
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
	char *path, *fullpath;

	if (av[0] == NULL)
	{
		free(av[0]);
		return (-1);
	}
	path = get_path();
	fullpath = find_command(av[0], path);
	if (fullpath == NULL)
	{
		fprintf(stderr, "%s: command not found\n", av[0]);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror(av[0]);
		return (-1);
	}
	if (pid == 0)
	{
		if ((execve(av[0], av, NULL) == -1))
		{
			perror(av[0]);
			return (-1);
		}
	}
	else
	{
		w = wait(&status);
		if (w == -1)
		{
			perror(av[0]);
			return (-1);
		}
	}
	return (0);
}
