#include "main.h"

/**
 * construct_full_path - Construct the full path for a command
 *
 * @dir: Directory from the PATH environment variable
 * @command: The command to append to the directory
 *
 * Return: A pointer to the constructed full path or NULL on failure
*/
char *construct_full_path(const char *dir, const char *command)
{

	char *full_path = malloc(strlen(dir) + strlen(command) + 2);

	if (full_path == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);


	return (full_path);
}

/**
 * check_command_in_path - Check if a command exists in the given path
 *
 * @full_path: The full path to the command
 *
 * Return: Full path to the command if found, otherwise NULL
*/
char *check_command_in_path(const char *full_path)
{
    char *found_command;
    size_t len;
    size_t i;

    if (full_path == NULL)
    {
        return (NULL);
    }
    if (access(full_path, X_OK) == 0)
    {
	    len = strlen(full_path) + 1;
	    found_command = malloc(len);
	    if (found_command == NULL)
	    {
		    perror("malloc");
		    return (NULL);
	    }
	    for (i = 0; i < len; i++)
	    {
		    found_command[i] = full_path[i];
	    }
	    return (found_command);
    }
    return (NULL);
}
