#include "main.h"

int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

	while (1)
	{
		/* Display prompt*/
		printf("$ ");
		fflush(stdout);

		/*Read command*/
		read = getline(&command, &len, stdin);
		
		if (read == -1)
		{
			printf("\n");
			break;
		}
		/* Remove newline character from the command */
		command[strcspn(command, "\n")] = 0;

		/* Createa child process to execute the command*/
		pid = fork();

		if (pid == 0)
		{
			/* In child process */
			char args[] = {command, NULL};
			execve(command, args,  NULL);

			/*if execv returns, it means the command was not found*/
			perror("simple_shell: command not found");
			exit(1);
		}
		else if (pid < 0)
		{
			/*Handle fork error */
			perror("simple_shell: error forking");
			continue;
		}
		else
		{
			/*I parent process, wait  for child to finish */
			waitpid(pid, &status, 0);
		}
	}
	/* Free memory allocated by getline */
	free(command);
	
	return (0);
}
