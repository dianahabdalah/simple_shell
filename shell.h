#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

/* Maximum length for user input and command */
#define MAX_INPUT_LENGTH 1024
#define MAX_ARG_LENGTH 64

/* Global environment variables */
extern char **environ;

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
char *_strdup(const char *str);
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, int c);
void _perror(char *prog_name, char *msg);
void free_args(char **args);

#endif /* SHELL_H */

