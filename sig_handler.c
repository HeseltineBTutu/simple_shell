#include "main.h"

/**
 * handle_sigint - Handles the SIGINT signal (Ctrl+C)
 * @sig: The signal number
 *
 * Description:
 * This function is a signal handler for the SIGINT signal (Ctrl+C).
 * It performs cleanup tasks and terminates the program gracefully.
 */
void handle_sigint(int sig)
{
	(void)sig;

	exit(EXIT_SUCCESS);
}
