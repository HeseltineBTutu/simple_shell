#include "main.h"
/**
 * find_command - searches for a command in the directories specified by PATH
 * @command: the command to search for
 * @path: the PATH environment variable
 *
 * Return: a pointer to the full path of the command, or NULL if not found
 */
char *find_command(char *command)
{
	char *dir, *fullpath = NULL;
	char *path;
	int i, j, len;

	path = getenv("PATH");
	if (command == NULL)
		return (NULL);
	/*check if the command was the full path and return it*/
	if ((access(command, F_OK) == 0))
		return (command);
	i = 0;
	while (path[i])
	{
		j = i;
		while (path[j] && path[j] != ':')
			j++;
		len = j - i;
		dir = malloc(sizeof(char) * (len + 2));
		if (dir == NULL)
			return (NULL);
		strncpy(dir, &path[i], len);
		strcat(dir, "/");
		fullpath = malloc(sizeof(char) * (len + strlen(command) + 2));
		if (fullpath == NULL)
		{
			free(dir);
			return (NULL);
		}
		strcpy(fullpath, dir);
		strcat(fullpath, command);
		free(dir);
		if (access(fullpath, F_OK) == 0)
			return (fullpath);
		i = j;
		if (path[i] == ':')
			i++;
	}
	return (NULL);
}
