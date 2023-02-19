#include "main.h"
/**
 * find - searches directory for an executable
 * @command: command to be searched
 * @dir: where to search
 * Return: 0 if found, -1 on error
 */
int find(char *command, DIR *dir)
{
	struct dirent *entry;
	int flag = -1;

	while ((entry = readdir(dir)))
	{
		if ((entry->d_ino && strstr(command, entry->d_name)))
		{
			flag = 0;
		}
	}
	return (flag);
}
/**
 * search - search path for a command
 * @command: command to be searched
 * Return: pointer to executable or NULL on error
 */
char *search(char *command)
{
	DIR *dir;
	char *path = getenv("PATH");
	char *token, *fullpath;
	char *cmd_cpy = strdup(command);

	if ((access(command, F_OK) == 0))
		return (command);
	token = strtok(path, ":");
	fullpath = malloc(20);
	if (!fullpath)
		return (NULL);
	while (token)
	{
		dir = opendir(token);
		if ((find(cmd_cpy, dir) == 0))
		{
			strcpy(fullpath, token);
			strcat(fullpath, "/");
			strcat(fullpath, cmd_cpy);
			return (fullpath);
		}
		else
		{
			closedir(dir);
		}
		token = strtok(NULL, ":");
	}
	free(cmd_cpy);
	free(fullpath);
	return (NULL);
}
