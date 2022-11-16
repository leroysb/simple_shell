#include "shell.h"

/**
* _strcat - concatenates two strings
* @dest: string 1
* @src: string 2
* Return: full string
*/
char *_strcat(char *dest, char *src)
{
	int len1, len2;

	len1 = 0;
	len2 = 0;

	while (dest[len1] != '\0')
		len1++;
	while (src[len2] != '\0')
	{
		dest[len1] = src[len2];
		len1++;
		len2++;
	}
	dest[len1] = '\0';
	return (dest);
}

/**
* _strlen - gets length of a string
* @string: subject string
* Return: length of string
*/
int _strlen(const char *string)
{
	int i;

	for (i = 0; string[i] != '\0'; i++)
		;
	return (i);
}

/**
* _getenv - scans through environment for specified variable
* @name: string containing name of variable to be searched for
* Return: string containing variable if found or NULL pointer if not found
*/
char *_getenv(const char *name)
{
	int len, i, j, count = 0;

	if (!name)
		return (NULL);
	len = _strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (environ[i][j] == name[j])
			{
				count++;
			}
		}
		if (count == j && count == len)
			return (environ[i]);
		count = 0;
	}
	return (NULL);
}

/**
* _stat - gets file status in specified directory
* @string: string containing name of file
* Return: 0 if file info was found in given directory, -1 otherwise
*/
int _stat(char *string)
{
	struct stat status;

	if (stat(string, &status) == 0)
		return (0);
	else
		return (-1);
}

/**
* pathifier - searches for location of executable file in the PATH
* @command: name of file to be searched for
* Return: string containing full path to executable if located, NULL otherwise
*/
char *pathifier(char *command)
{
	char *temp, *path, *dir_string, **directories, *delim = ":";
	int i, j = 0, k = 0, val = 0;

	if (command[0] == '.' || command[0] == '/')
	{
		temp = malloc(sizeof(char) * (_strlen(command)));
		return (_strcat(temp, command));
	}
	path = _getenv("PATH");
	if (path)
	{
		dir_string = malloc(sizeof(char) * (_strlen(path)));
		for (i = 0; path[i] != '\0'; i++)
		{
			if (path[i] == '/')
				val = 1;
			if (val)
			{
				dir_string[j] = path[i];
				j++;
			}
		}
		directories = malloc(sizeof(char) * (_strlen(dir_string)) + 20);
		directories[k] = strtok(dir_string, delim);
		while (directories[k])
		{
			temp = malloc(sizeof(char) * (_strlen(directories[k])) + 10);
			_strcat(temp, directories[k]);
			_strcat(temp, "/");
			if (_stat(_strcat(temp, command)) == 0)
				break;
			k++;
			directories[k] = strtok(NULL, delim);
			free(temp);
			temp = NULL;
		}
	}
	free(dir_string);
	free(directories);
	return (temp);
}
