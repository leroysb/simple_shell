#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int _len(char *string)
{
	int i;

	for (i = 0; string[i] != '\0'; i++)
		;
	return (i);
}

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


int main(void)
{
	char *buffer, **tokens, *delim = " \t\n";
	size_t bufsize = sizeof(char) * 1;
	int i = 0, exitcode = 0, exec = 0;
	pid_t pid;

	while (!exitcode)
	{
		buffer = NULL;
		tokens = NULL;
		printf("-> ");
		getline(&buffer, &bufsize, stdin);
		exit_status(buffer, &exitcode);
		if (exitcode)
			break;
		tokens = malloc(1024);

	
		while (tokens[i - 1] || i < 1)
		{
			if (i < 1)
			{
				tokens[i] = strtok(buffer, delim);
			}
			else
			{
				tokens[i] = strtok(NULL, delim);
			}
			i++;
		}
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			//printf("token: %s\nexec: %d\n", tokens[1], exec);
			exec = execve(tokens[0], tokens, NULL);
			if (exec == -1)
			{
				perror ("execve");
				free(buffer);
				free(tokens);
				exit(0);
			}

		}
		else
			wait(NULL);
		free(tokens);
		free(buffer);
	}
	free(tokens);
	free(buffer);
	return (0);
}
