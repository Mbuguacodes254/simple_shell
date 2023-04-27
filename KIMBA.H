#ifndef _KIMBA_H_
#define _KIMBA_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_getinput 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct li_st_str - singly linked list
 * @num: number field
 * @str: the string
 * @next: this points to the next node
 */
typedef struct li_st_str
{
	int num;
	char *str;
	struct li_st_str *next;
} list_t;

/**
 * struct passinfo - holds the pseudo-arguements to be passed into a function,
 * thus allowing uniform prototype for function pointer struct
 * @arg: is a string initiated from getline which contains arguements
 * @argv: is an array of strings initiated from arg
 * @path: shows the string path for the current command
 * @argc: shows the argument count
 * @line_count: shows the error count
 * @err_num: is the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program's filename
 * @env: is the linked list for the local copy of environ
 * @environ: holds the custom modified copy of environ from LL env
 * @history: shows history node
 * @alias: shows alias node
 * @env_changed: on if environ was changed
 * @status: shows the return status of the last executed command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buffer_type: CMD_type ||, &&, ;
 * @readfd: the fd from where to read line input
 * @histcount: history line number count
 */
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buffer_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - holds builtin string and affiliated function
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/*  prototypes for shell_file_loop */
int hsh(info_t *, char **);
int _findbuiltin(info_t *);
void _findcommand(info_t *);
void _forkdcommand(info_t *);

/*  prototypes for file_parser.c */
int is_command(info_t *, char *);
char *dup_chars(char *, int, int);
char *_findpath(info_t *, char *, char *);

/*  prototypes for err_0.c */
void eputs_(char *);
int _e_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/*  prototypes for strng_0.c */
int string_len(char *);
int str_cmp(char *, char *);
char *starts_with(const char *, const char *);
char *str_cat(char *, char *);

/*  prototypes for strng_1.c */
char *str_copy(char *, char *);
char *str_duplicate(const char *);
void puts_(char *);
int _putchar(char);

/*  prototypes for exit_code.c */
char *string_cpy(char *, char *, int);
char *string_cat(char *, char *, int);
char *string_char(char *, char);

/*  prototypes for token_file.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/*  prototypes for file_realloc.c */
char *_memset(char *, char, unsigned int);
void f_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*  prototypes for mem_file.c */
int b_free(void **);

/*  prototypes for  ATOI.c */
int _interactive(info_t *);
int isdelim(char, char *);
int is_alpha(int);
int atoi(char *);

/*  prototypes for err_01.c */
int err_atoi(char *);
void prt_err(info_t *, char *);
int prt_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*  prototypes for builtin_0.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/*  prototypes for builtin_01.c */
int my_hist(info_t *);
int my_alias(info_t *);

/* prototypes for get_inf_o.c */
ssize_t _getinput(info_t *);
int _getinput(info_t *, char **, size_t *);
void __sigintHandler(int);
void _clearinfo(info_t *);
void _setinfo(info_t *, char **);
void _freeinfo(info_t *, int);

/*  prototypes for our_environment.c */
char *get_env(info_t *, const char *);
int my_env(info_t *);
int myset_env(info_t *);
int myunset_env(info_t *);
int populate_envlist(info_t *);
char **get_env(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/*  prototypes for hist_file.c */
char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renum_hist(info_t *info);

/*  prototypes for li_st_s.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t _printlist_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void _free_list(list_t **);

/*  prototypes for lists_01.c */
size_t list_length(const list_t *);
char **list_to_strings(list_t *);
size_t _printlist(const list_t *);
list_t *node_startswith(list_t *, char *, char);
ssize_t get_index_node(list_t *, list_t *);

/*  prototypes for variables.c */
int _ischain(info_t *, char *, size_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int rep_variiables(info_t *);
int rep_strng(char **, char *);

#endif
