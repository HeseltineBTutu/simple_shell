#include "main.h"
/**
 * find_command - searches for a command in the directories specified by PATH
 * @command: the command to search for
 *
 * Return: a pointer to the full path of the command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

<<<<<<< HEAD
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
=======
	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
>>>>>>> 1dc4da63f727d150ad2de2fc0790350ab30338fe
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
