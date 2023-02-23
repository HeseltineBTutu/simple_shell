#include "main.h"
/**
 * sigint_handler
 *
 */
void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(0);
	}
}
