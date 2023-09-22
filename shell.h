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

/* Constants for buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Constants for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Constants for number conversion */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flag for using system's getline function */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* File for maintaining shell history and maximum history size */
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* External environment variables */
extern char **environ;

/* Structure for singly linked list of strings */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/* Structure for passing information to functions */
typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

/* Initialization for info_t structure */
#define INFO_INIT \
{ \
    NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0 \
}

/* Function prototypes */
int initialize_shell(info_t *, char **);
int locate_builtin_command(info_t *);
int is_valid_command(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_executable_path(info_t *, char *, char *);
int interactive_shell(info_t *);
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);
int display_history(info_t *);
int handle_alias(info_t *);
ssize_t read_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void handle_interrupt(int);
void clear_shell_info(info_t *);
void setup_shell_info(info_t *, char **);
void free_shell_info(info_t *, int);
char *get_environment_variable(info_t *, const char *);
int display_environment(info_t *);
int set_environment_variable(info_t *);
int unset_environment_variable(info_t *);
int populate_environment_list(info_t *);
char **get_updated_environment(info_t *);
int remove_environment_variable(info_t *, char *);
int add_environment_variable(info_t *, char *, char *);
char *get_history_file_path(info_t *);
int write_shell_history(info_t *);
int read_shell_history(info_t *);
int build_history_list(info_t *, char *buf, int linecount);
int renumber_shell_history(info_t *);
list_t *add_string_node(list_t **, const char *, int);
list_t *add_string_node_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int delete_string_node_at_index(list_t **, unsigned int);
void free_string_list(list_t **);
size_t get_string_list_length(const list_t *);
char **convert_string_list_to_array(list_t *);
size_t print_list(const list_t *);
list_t *find_string_node_starts_with(list_t *, char *, char);
ssize_t find_string_node_index(list_t *, list_t *);
int is_command_chain(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_in_input(info_t *);
int replace_environment_variables(info_t *);
int replace_string_in_buffer(char **, char *);

#endif /* _SHELL_H_ */

