#include "main.h"

/*
 * set_env_variable - Set or update an environment variable
 *
 * @variable: Name of the environment variable
 * @value: Value to set for the environment variable
 * Return: 0 on success, -1 on failure
 */
int set_env_variable(const char *variable, const char *value)
{
	if (!variable || !value)
	{
		return(-1);
	}
	if (setenv(variable, value, 1) != 0)
	{
		perror("setenv");
	}
	return (0);
}

/**
 * unset_env_variable - Unset an environment variable
 *
 * @variable: Name of the environment variable to unset
 * Return: 0 on success, -1 on failure
 */
int unset_env_variable(const char *variable)
{
	if (!variable)
	{
		return (-1);
	}
	if (unsetenv(variable) != 0)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}
