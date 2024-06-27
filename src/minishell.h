# ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>

int exit_code;

typedef enum e_enum
{
	INIT = 1,
	HERE,
	CMD,
	IGN
}t_enum;

typedef struct s_split
{
        int i;
        int cmd;
        char *char_set;
        char **send;
		char *str;

} t_split;

typedef struct s_count
{
	char *str;
	int i;

}t_count;

typedef struct s_check
{
	int here_doc;
	int here_doc_mark;
	int q_mark;
	int qq_mark;
	int re_direction_mark;
	int error;
	int export;
	struct s_check *next;

}t_check;

typedef struct s_cmd
{
	pid_t child;
	int fd[2];
	char *infile;
	int infile_fd;
	char *outfile;
	int outfile_fd;
	char *cmd[10];
	char *here_doc;
	int here_doc_fd;
	int append;
	int i;
	struct s_cmd *next;
}t_cmd;

typedef struct s_main
{
	int fd_tmp;
	int std[2];
	int cmd_list_num;
	char *input;
	char **cmd;
	char **envp;
	char **path;
	struct s_envp *envp_list;
	struct s_cmd *cmd_list;
	int exit_state;
	char *save_pwd;

}t_main;

typedef struct s_envp
{
	char *key;
	char *value;
	struct s_envp *next;
}t_envp;

typedef enum e_syn
{
	FIR,
	RED,
	PIP,
	DAL,
	ARG
}t_syn;
void    print_error(char *cmd, char *message);
void sig_init (int option);
void sigint_handler (int signum);
void here_doc_sigint_handler (int signum);
void here_doc_sigquit_handler (int signum);
void sigquit_handler (int signum);
void env_process(t_main *main);
int echo(char **cmd);
int error_message(char *str, int error_num);
int pwd(t_main *main);
char *get_env(t_envp *env, char *str);
int cd(t_main *main, char *cmd);
int unset_built(t_main *main, char **cmd);
int export_built(t_main *main, char **cmd);
int check_builtin(t_cmd *list);
int do_builtin(t_cmd *list, t_main *main);
int ft_stcmp(char s1, char *s2);
char **ft_split_set(char *str, char *charset);
int ft_strcmp(char *s1, char *s2);
void here_doc (t_check *cmd, char mark);
int q_mark (t_check *cmd, char *mark);
void make_envp(t_main *main, char *arr);
void defult_envp(t_main *main);
void print_envp(t_main *main, int env);
void free_cmd(t_main *main);
void free_cmdlist(char **cmd);
void free_envp(t_envp *envp);
void free_envplist(t_envp *envp);
void add_envpnode(t_envp **list, t_envp *new);
t_envp *make_envpnode(char *key, char *value);
int delete_env(t_main *main, char *key);
int check_already_add(t_main *main, char *key, char *value);
char *replace_cmd(t_main *main, char *cmd);
char *value_check(char *value);
void print_cmd(t_main *main);
int make_cmd(t_main *main);
int split_cmd(t_main *main);
int cmd_check(char *str);
int get_next(t_main *main, int i);
t_cmd *make_node(t_main *main, int i, int j);
void add_node(t_cmd **list, t_cmd *new);
int exit_num(char **cmd);
/////////////////////////////
int	cmd_path(t_main *main, t_cmd *cmd);
int do_cmd(t_main *main);
char **make_envp_arr(t_envp *lst);
void	print_error(char *cmd, char *message);

# endif
