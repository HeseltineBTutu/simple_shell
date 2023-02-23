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

	if ((access(command, F_OK | X_OK) == 0))
		return (command);
	path = getenv("PATH");
	if (path == NULL)
		return (0);
	i = 0;
	while (path[i])
	{
		j = i;
		while (path[j] && path[j] != ':')
			j++;
		len = j - i;
		dir = malloc(sizeof(char) * len + 2);
		if (dir == NULL)
			return (0);
		strncpy(dir, &path[i], len);
		dir[len] = '/';
		dir[len + 1] = '\0';
		fullpath = malloc(sizeof(char) * (len + strlen(command) + 2));
		if (fullpath == NULL)
		{
			free(dir);
			return (0);
		}
		strcpy(fullpath, dir);
		strcat(fullpath, command);
		free(dir);
		if (access(fullpath, F_OK) == 0)
		{
			return (fullpath);
		}
		free(fullpath);
		i = j;
		if (path[i] == ':')
			i++;
	}
	free(&path[i]);
	return (0);
}
int main()
{
	char *cmd = "ls";
	char *path = find_command(cmd);
	printf("%s\n", path);
}
