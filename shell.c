#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
char *input;
char **args;
int status;
while (1)
{
/* Display the prompt */
display_prompt();
/* Read user input */
input = read_input();

/* Parse user input into arguments */
args = parse_input(input);

/* Execute the command */
status = execute_command(args);

/* Free allocated memory */
free(input);
free_args(args);

/* Exit the shell on certain conditions */
if (status == -1)
break;
}
return (0);
}

