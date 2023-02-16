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
	char *command;

	(void)argc;
	/*assign argv to global variable arr for error handling*/
	arr = argv;
	while (1)
	{
		write(STDOUT_FILENO, prompt, 9);
		fflush(stdout);

		command = get_command();
		execute_command(command);
		free(command);
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
 * execute_command - Execute a command in a childe process.
 * @command: Pointer to the command string.
 */
void execute_command(char *command)
{
	char *av[BUFSIZE];
	char *token, delim[] = " \t\r\n";
	int status, i = 0;
	pid_t pid;

	/* Split the command line into separate arguments*/
	token = strtok(command, delim);
	while (token)
	{
		av[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	av[i] = NULL;
	/* Create a child process to execute the command */
	pid = fork();
	if (pid == 0)
	{
		/* In child process */
		if (av[0] == NULL)
		{
			free(command);
			exit(0);
		}
		execve(av[0], av, environ);
		/* If execve returns, it means the command was not found*/
		perror(arr[0]);
		exit(1);
	}
	else if (pid < 0)
	{
		/*Handle fork error*/
		perror(arr[0]);
	}
	else
	{
		/* In parent process, wait for child to finish */
		waitpid(pid, &status, 0);
	}
}
