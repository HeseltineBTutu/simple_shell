#include "main.h"

/**
<<<<<<< HEAD
 * built_in_exit - built-in function to exit the shell
 * @av: command line arguments
 * Return: 0 on success, or an error code if there was an error
 */
int built_in_exit(char **av)
{
  int status = 0;
  char *endptr;

  if (av[0] == NULL || strcmp(av[0], "exit") != 0)
    return (0); /* not the exit command */
/** built_in_exit - exit shell
 *
 * Return: Always returns 0, to proceed with execution.
 */
int built_in_exit(void)
{
	 _exit(0);
}
  if (av[1] != NULL)
  {
    /* parse exit status from command line argument */
    status = strtol(av[1], &endptr, 10);
    if (*endptr != '\0')
    {
      fprintf(stderr, "exit: invalid argument '%s'\n", av[1]);
      return (-1);
    }
  }
  else if (getenv("$?") != NULL)
  {
    /* parse exit status from environment variable */
    status = strtol(getenv("$?"), &endptr, 10);
    if (*endptr != '\0')
    {
      fprintf(stderr, "exit: invalid environment variable '$?'\n");
      return (-1);
    }
  }

  /* check if exit status is in range */
  if (status < 0 || status > 255)
  {
    fprintf(stderr, "exit: exit status out of range\n");
    return (-1);
  }

  /* free memory and exit */
  free(av);
  exit(status);
}
/**
 * built_in_env - print the current environment
 *
 * Return: Always returns 0, to proceed with execution.
 */
int built_in_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
/**
 * execute_built_in - executes env and exit
 * @command: array of strings
 */
void execute_built_in(char **command)
{
	if (strcmp(command[0], "exit") == 0)
	{
		free(command[0]);
		free(command);
		built_in_exit();
	}
	if (strncmp(command[0], "env", 3) == 0)
	{
		built_in_env();
	}
}
