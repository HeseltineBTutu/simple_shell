#include "main.h"
/**
 * main - Entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char *prompt = "#cisfun$ ";
	char *command= NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	
	while (1)
	{
		printf("%s", prompt);
		fflush(stdout);
		read = getline(&command, &len, stdin);
		if (read == -1)
		{
			/*Handle end of file (Ctrl + D)*/
			printf("\n");
			break;
		}
		/* Create a child process to execute the command */
		pid = fork();
		if (pid == 0)
		{
			/*In child process*/
			char *argv[] = {command, NULL};
			execve(command, argv, environ);

			/*If execve returns, itmeans the command was not found*/
			perror("#cisfun");
			exit(1);
		}
		else if (pid < 0)
		{
			/*Handle fork error*/
			perror("#cisfun: error forking");
			continue;
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
