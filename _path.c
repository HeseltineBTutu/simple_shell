#include "main.h"
/**
 * find_command - searches for a command in the directories specified by PATH
 * @command: the command to search for
 *
 * Return: a pointer to the full path of the command, or NULL if not found
 */
char *find_command(char *command)
{
	char *dir;
	char *fullpath;
	char *path;
	int i, j, len;

	if ((access(command, F_OK) == 0))
		return (command);
	path = getenv("PATH");
	if (path == NULL || strlen(path) == 0)
	{
		if ((access(command, F_OK) == 0))
			return (command);
		return (NULL);
	}
	i = 0;
	while (path[i])
	{
		j = i;
		while (path[j] && path[j] != ':')
			j++;
		len = j - i;
		dir = malloc(sizeof(char) * len + 2);
		if (dir == NULL)
			return (NULL);
		strncpy(dir, &path[i], len);
		dir[len] = '/';
		dir[len + 1] = '\0';
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
		free(fullpath);
		i = j;
		if (path[i] == ':')
			i++;
	}
	return (NULL);
}
