#include "main.h"

/**
 * main - Starts the shell program
 *
 * Return: 0 on success.
 */
int main(void)
{
	char *prompt = "#cisfun$ ";
	char *command;

	while (1)
	{
		printf("%s", prompt);
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
 * Return: POinter to the command string.
 */
char *get_command(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read = getline(&command, &len, stdin);

	if (read == -1)
	{
		printf("\n");
		exit(-1);
	}
	return (command);
}

/**
 * execute_command - Execute a command in a childe process.
 * @command: Pointer to the command string.
 */
void execute_command(char *command)
{
	char *argv[BUFSIZE];
	char *token, delim[] = " \t\r\n";
	int status, count = 0, i = 0;
	pid_t pid;

	/* Split the command line into separate arguments*/
	token = strtok(command, delim);
	while (token)
	{
		argv[i] = token;
		count++;
		i++;
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	/* Create a child process to execute the command */
	pid = fork();
	if (pid == 0)
	{
		if ((strcmp(command, "\n") == 0))
			exit(0);
		/* In child process */
		execve(argv[0], argv, environ);
		/* If execve returns, it means the command was not found*/
		perror("cisfun");
		exit(0);
	}
	else if (pid < 0)
	{
		/*Handle fork error*/
		perror("cisfun");
	}
	else
	{
		/* In parent process, wait for child to finish */
		waitpid(pid, &status, 0);
	}
}
