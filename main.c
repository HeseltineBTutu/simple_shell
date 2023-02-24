#include "main.h"
/**
 * sighan - block control c signal
 * @signum: action for signal
 */
void sighan(__attribute__((unused)) int signum)
{
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}
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
	signal(SIGINT, sighan);
	while (1)
	{
		/*check if stdin is open to determine interactive or non interactive mode*/
		if ((isatty(STDIN_FILENO)))
			printf("%s", prompt);
		read = getline(&command, &len, stdin);
		if (read == -1)
		{
			/*check if getline failed because of end of file or due to error*/
			if (feof(stdin))
			{
				free(command);
				return (0);
			}
			else
			{
				perror("getline");
				free(command);
				return (0);
			}
		}
		args = getargs(command);
		execute(args);
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
	char *fullpath;

	if (av[0] == NULL)
	{
		free(av);
		return (-1);
	}
	fullpath = find_command(av[0]);
	built_in_exit(av);
	if (fullpath == NULL)
	{
		fprintf(stderr, "%s: command not found\n", arr[0]), free(av);
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
		execve(fullpath, av, environ);
		perror(arr[0]);
		return (-1);
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
	free(fullpath);
	free(av);
	return (0);
}
