#include "main.h"

int main(/*int ac, char **argv*/)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;
	char *lineptr_copy = NULL, *lineptr = NULL;
	const char *delim = "\n";
	char *token;
	int num_tokens = 0;
	int i, status;
	pid_t pid;
	char *argv[] = {"", NULL};

	/*(void) ac; */
	while (1)
	{
		/* Display prompt*/
		printf("$ ");

		/*Read command*/
		read = getline(&command, &len, stdin);
		token = strtok(command, delim);
		if (read == -1)
		{
			printf("\n");
			break;
		}
		pid = fork();
		if (pid < 0)
			perror("simple_shell");
		if (pid == 0)
		{
			if ((execve(token, argv, NULL)) == -1)
				perror("simple_shell");
			exit(0);
		}
		waitpid(pid, &status, 0);
	}
	/* allocate space for a copy of the lineptr 

	lineptr_copy = malloc(sizeof(char) * read);
	if (lineptr_copy == NULL)
	{
		perror("simple_shell:" );
		return (-1);
	}
	*copy lineptr to lineptr_copy
	strcpy(lineptr_copy, lineptr);
	token = strtok(lineptr, delim);

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;

	*Allocate space to hold the array of strings
	argv = malloc(sizeof(char *) * num_tokens);
	*Store each token in argv array
	token = strtok(lineptr_copy, delim);

	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	printf("%s\n", lineptr);
	* Free memory allocated by getline */
	free(command);
	return (0);
}
