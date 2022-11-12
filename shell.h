#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

int main(int ac, char **av);

/* builtins */
int num_builtins(void);
int shell_cd(char **args);
int shell_exit(char **args);
int launch(char **args);
int execute(char **args);

/* handlers */
char *read_line(void);
char **split_line(char *line);
void shell_loop(void);

#endif
