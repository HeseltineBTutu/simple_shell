#include "main.h"
/**
 * main - Entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char *prompt = "#cisfun$ ";
	char *command = NULL, *token;
	char *argv[BUFSIZE];
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status, i;
	
	while (1)
	{
		printf("%s", prompt);
		fflush(stdout);
		read = getline(&command, &len, stdin);
		if (read == -1)
		{
			/*Handle end of file (Ctrl + D)*/
			printf("\n");
			exit(1);
		}
		/*Split the command line into separate arguments */
		token = strtok(command, "\n");
		argv[0] = strtok(command, " ");
		for (i = 1; i < BUFSIZE; i++)
		{
			argv[i] = strtok(NULL, " ");
			if (argv[i] == NULL)
				break;
		}
		/* Create a child process to execute the command */
		pid = fork();
		if (pid == 0)
		{
			char *argv[] = {"command", NULL};
			/*In child process*/
			if (strcmp(command, "\n") == 0)
				exit(0);
			execve(token, argv, environ);
			/*Ignore new line character*/
			/*If execve returns, itmeans the command was not found*/
			perror("#cisfun");
			exit(0);
		}
		else if (pid < 0)
		{
			/*Handle fork error*/
			perror("#cisfun: error forking");
		}
		else
		{
			/*In parent process, wait for child to finish*/
			waitpid(pid, &status, 0);
		}


	}
	free(command);
	return (0);
}
