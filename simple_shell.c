#include "main.h"

int main(int ac, char **argv)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;
	(void) ac; (void) argv;

	while (1)
	{
		/* Display prompt*/
		printf("$ ");

		/*Read command*/
		read = getline(&command, &len, stdin);
		
		if (read == -1)
		{
			printf("\n");
			break;
		}
	}
	/* Free memory allocated by getline */
	free(command);
	
	return (0);
}
