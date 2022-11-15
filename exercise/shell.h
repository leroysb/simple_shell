#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

/* HEADER FILES */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

/* VARIABLES */
extern char **environ;

/* PROTOTYPES */
int _putchar(char c);
int nextline(char *string);
void exit_status(char *string, int *ptr);
void child(char **tokens, char *buffer);
char *_strcat(char *dest, char *src);
int _strlen(const char *string);
char *_getenv(const char *name);
int _stat(char *string);
char *pathifier(char *command);

#endif /* SIMPLE_SHELL */
