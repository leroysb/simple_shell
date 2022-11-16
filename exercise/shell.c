#include "shell.h"

/**
* nextline - checks if user hit return key without any other input
* @string: string containing user input
* Return: 1 to indicate input contained newline char only or 0 if not
*/
int nextline(char *string)
{
	int i = 0;

	while (string[i] != '\n')
		i++;
	if (i == 0)
		return (1);
	else
		return (0);
}

/**
* exit_status - checks for program termination command
* @string: string containing user input
* @ptr: pointer to exit trigger value in program
*/
void exit_status(char *string, int *ptr)
{
	int i, count = 0;
	char *exit = "exit";

	for (i = 0; i < 4; i++)
	{
		if (string[i] == exit[i])
			count++;
	}
	if (count == 4)
		if (string[count] == '\n' || string[count] == ' ')
			*ptr = 1;
}

/**
* child - forks a child process and executes passed command in forked instance
* @tokens: array of strings containing passed command and arguments
* @buffer: string holding input from user to be freed if execution fails
*/
void child(char **tokens, char *buffer)
{
	int exec, i;
	pid_t pid;
	char *command = pathifier(tokens[0]), *error = ": command not found";

	if (command)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(0);
		}
		if (pid == 0)
		{
			exec = execve(command, tokens, environ);
			if (exec == -1)
			{
				perror(tokens[0]);
				free(buffer);
				free(tokens);
				exit(0);
			}
		}
		else
			wait(NULL);
	}
	else
	{
		for (i = 0; tokens[0][i]; i++)
			_putchar(tokens[0][i]);
		for (i = 0; error[i]; i++)
			_putchar(error[i]);
		_putchar('\n');
	}
	free(command);
}

/**
* _signal - handles ^C
* @z: unused variable
*/
void _signal(__attribute__((unused)) int z)
{
	_putchar('\n');
	_putchar('$');
	_putchar(' ');
}

/**
* main - program start point
* Return: 0
*/
int main(void)
{
	char *buffer = NULL, **tokens = NULL, *delim = " \t\n";
	size_t bufsize = sizeof(char) * 1;
	int i = 0, exitcode = 0;

	_putchar('$');
	_putchar(' ');
	signal(SIGINT, _signal);
	if (getline(&buffer, &bufsize, stdin) == -1)
		_putchar('\n');
	else
	{
		exit_status(buffer, &exitcode);
		if (!exitcode)
		{
			if (!nextline(buffer))
			{
				tokens = malloc(1024);
				while (tokens[i - 1] || i < 1)
				{
					if (i < 1)
						tokens[i] = strtok(buffer, delim);
					else
						tokens[i] = strtok(NULL, delim);
					i++;
				}
				child(tokens, buffer);
				free(tokens);
			}
			main();
		}
	}
	free(buffer);
	return (0);
}
