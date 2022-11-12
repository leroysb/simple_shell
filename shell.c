#include "shell.h"

/**
 * main - sets shell loop function.
 *
 * @ac: argument count
 * @av: argument vector
 * Return: Exits if successful.
 */
int main(int ac, char **av)
{
	ac = ac;
	av = av;
	printf("A custom C-shell");
	shell_loop();
	return (EXIT_SUCCESS);
}
