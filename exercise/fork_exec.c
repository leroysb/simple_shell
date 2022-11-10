#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
	int i = 0, exec;
	pid_t pid;
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	while (i < 5)
	{
		pid = fork();
		i++;
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			exec = execve(argv[0], argv, NULL);
			if (exec == -1)
				return (-1);
		}
		else
			wait(NULL);
		if (i < 5)
			printf("\n\n\n");
	}
	return (0);
}
