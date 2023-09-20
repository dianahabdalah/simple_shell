#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Define read and write buffer sizes */
#define CUSTOM_READ_BUFFER_SIZE 1024
#define CUSTOM_WRITE_BUFFER_SIZE 1024
#define CUSTOM_BUFFER_FLUSH -1

/* Define command chaining types */
#define CUSTOM_CMD_NORMAL 0
#define CUSTOM_CMD_OR 1
#define CUSTOM_CMD_AND 2
#define CUSTOM_CMD_CHAIN 3

/* Define conversion options */
#define CUSTOM_CONVERT_LOWERCASE 1
#define CUSTOM_CONVERT_UNSIGNED 2

/* Flag for system getline() usage */
#define CUSTOM_USE_GETLINE 0
#define CUSTOM_USE_STRTOK 0

#define CUSTOM_HISTORY_FILE ".my_shell_history"
#define CUSTOM_HISTORY_MAX 4096

extern char **custom_environment;

/**
 * struct CustomStringList - singly linked list of strings
 * @num: number field
 * @str: string
 * @next: points to the next node
 */
typedef struct CustomStringList
{
    int num;
    char *str;
    struct CustomStringList *next;
} custom_list_t;

/**
 * struct CustomShellInfo - contains pseudo-arguments to pass into a function,
 * allowing uniform prototypes for function pointer struct
 * @custom_args: string from getline containing arguments
 * @custom_argv: array of strings from args
 * @custom_path: path for the current command
 * @custom_argc: argument count
 * @custom_line_count: error count
 * @custom_err_num: error code for exit() calls
 * @custom_linecount_flag: flag to count lines of input
 * @custom_fname: program filename
 * @custom_env_list: linked list local copy of environ
 * @custom_history: history node
 * @custom_alias: alias node
 * @custom_env_modified: flag for changes to environ
 * @custom_exit_status: return status of the last executed command
 * @custom_cmd_buffer: address of pointer to command buffer, for chaining
 * @custom_cmd_buffer_type: command type (normal, ||, &&, etc.)
 * @custom_read_fd: file descriptor for reading input
 * @custom_hist_count: history line number count
 */
typedef struct CustomShellInfo
{
    char *custom_args;
    char **custom_argv;
    char *custom_path;
    int custom_argc;
    unsigned int custom_line_count;
    int custom_err_num;
    int custom_linecount_flag;
    char *custom_fname;
    custom_list_t *custom_env_list;
    custom_list_t *custom_history;
    custom_list_t *custom_alias;
    char **custom_environment;
    int custom_env_modified;
    int custom_exit_status;
    char **custom_cmd_buffer;
    int custom_cmd_buffer_type;
    int custom_read_fd;
    int custom_hist_count;
} custom_info_t;

#define CUSTOM_INFO_INIT \
{ \
    NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0 \
}

/**
 * struct CustomBuiltinCommand - contains a builtin string and related function
 * @custom_type: builtin command flag
 * @custom_func: function pointer
 */
typedef struct CustomBuiltinCommand
{
    char *custom_type;
    int (*custom_func)(custom_info_t *);
} custom_builtin_table;

/* Function prototypes for shell operations */
int custom_start_shell(custom_info_t *, char **);
int custom_find_builtin(custom_info_t *);
void custom_find_command(custom_info_t *);
void custom_fork_command(custom_info_t *);

/* Other function prototypes */
void custom_print_error(custom_info_t *, char *);
void custom_remove_comments(char *);
int custom_is_command(custom_info_t *, char *);
char *custom_duplicate_characters(char *, int, int);
char *custom_find_executable(custom_info_t *, char *, char *);
ssize_t custom_get_input(custom_info_t *);
int custom_get_line(custom_info_t *, char **, size_t *);
void custom_sigint_handler(int);

/* Memory management prototypes */
int custom_free_buffer(void **);
int custom_free_list(custom_list_t **);
char **custom_list_to_strings(custom_list_t *);
int custom_replace_string(char **, char *);
int custom_replace_alias(custom_info_t *);
int custom_replace_variables(custom_info_t *);

/* Builtin command prototypes */
int custom_my_exit(custom_info_t *);
int custom_my_cd(custom_info_t *);
int custom_my_help(custom_info_t *);
int custom_my_history(custom_info_t *);
int custom_my_alias(custom_info_t *);
int custom_my_env(custom_info_t *);
int custom_my_setenv(custom_info_t *);
int custom_my_unsetenv(custom_info_t *);

/* History-related prototypes */
char *custom_get_history_file(custom_info_t *);
int custom_write_history(custom_info_t *);
int custom_read_history(custom_info_t *);
int custom_build_history_list(custom_info_t *, char *, int);
int custom_renumber_history(custom_info_t *);

#endif

