/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:48:48 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 10:30:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>

int			g_exit_code;

typedef enum e_enum
{
	INIT = 1,
	HERE,
	CMD,
	IGN
}					t_enum;

typedef struct s_pwd
{
	char			*w_pwd;
	char			*w_old;
	char			*w_path;
	char			*old_pwd;

}					t_pwd;
typedef struct s_split
{
	int				i;
	int				cmd;
	char			*char_set;
	char			**send;
	char			*str;

}					t_split;

typedef struct s_count
{
	char			*str;
	int				i;

}					t_count;

typedef struct s_check
{
	int				here_doc;
	int				here_doc_mark;
	int				q_mark;
	int				qq_mark;
	int				re_direction_mark;
	int				error;
	struct s_check	*next;

}					t_check;

typedef struct s_cmd
{
	pid_t			child;
	int				fd[2];
	char			*infile;
	int				infile_fd;
	char			*outfile;
	int				outfile_fd;
	char			*cmd[1024];
	char			*here_doc;
	int				here_doc_fd;
	int				append;
	int				i;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_main
{
	int				fd_tmp;
	int				std[2];
	int				cmd_list_num;
	char			*input;
	char			**cmd;
	char			**envp;
	char			**path;
	struct s_envp	*envp_list;
	struct s_cmd	*cmd_list;
	int				exit_state;
	char			*save_pwd;
	int				read_error;

}					t_main;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef enum e_syn
{
	FIR,
	RED,
	PIP,
	DAL,
	HER,
	ARG,
	QQ,
	Q,
	EOD
}					t_syn;

typedef struct s_splitcmd
{
	int				i;
	int				j;
	int				k;
	int				first;
	char			m;
}					t_splitcmd;

void				print_error(char *cmd, char *message);
void				sig_init(int option);
void				sigint_handler(void);
void				here_doc_sigint_handler(int signum);
void				here_doc_sigquit_handler(int signum);
void				sigquit_handler(int signum);
void				env_process(t_main *main);
char				*to_char_nomal(char *s);
char				*to_char_op(char *s);
int					echo(char **cmd);
int					error_message(char *str, int error_num);
int					pwd(t_main *main);
char				*get_env(t_envp *env, char *str);
int					cd(t_main *main, char *cmd);
int					unset_built(t_main *main, char **cmd);
int					export_built(t_main *main, char **cmd);
int					check_builtin(t_cmd *list);
int					do_builtin(t_cmd *list, t_main *main);
int					ft_stcmp(char s1, char *s2);
char				**ft_split_set(char *str, char *charset);
int					ft_strcmp(char *s1, char *s2);
void				here_doc(t_check *cmd, char mark);
int					check_envsyn_error(char *key, char *value);
char				*q_remover(char *s);
char				*q_remover_head(char *s);
char				*q_remover_tail(char *s);
int					q_mark(t_check *cmd, char *mark);
int					make_envp(t_main *main, char *arr);
void				defult_envp(t_main *main);
void				print_envp(t_main *main, int env);
void				free_cmd(t_main *main, int end);
void				free_cmdlist(char **cmd);
char				*re_ascii(char *s, int option);
void				free_envp(t_envp *envp);
void				free_envplist(t_envp *envp);
void				add_envpnode(t_envp **list, t_envp *new);
t_envp				*make_envpnode(char *key, char *value);
int					delete_env(t_main *main, char *key);
int					check_already_add(t_main *main, char *key, char *value);
char				*replace_cmd(t_main *main, char *cmd);
char				*value_check(char *value);
void				print_cmd(t_main *main);
int					make_cmd(t_main *main);
int					split_cmd(t_main *main);
int					cmd_check(char *str);
int					get_next(t_main *main, int i);
t_cmd				*make_node(t_main *main, int i, int j);
void				add_node(t_main *main, t_cmd *new);
int					exit_num(char **cmd);
int					cmd_path(t_main *main, t_cmd *cmd);
int					do_cmd(t_main *main);
char				**make_envp_arr(t_envp *lst);
void				in_mark(t_check *cmd);
void				out_mark(t_check *cmd);
void				qq_note(t_check *cmd);
void				q_note(t_check *cmd);
void				q_swap(t_check *cmd, char *mark, int i);
int					triple_strcmp(char *str, char *set);
int					triple_char(char *str);
void				eof_doller(char *str);
int					error_cmd(char *str);
void				str_int(char *str);
int					check_mark(char input);
int					continuous_check_mark(t_main *main, t_splitcmd *s_cmd);
int					space_between_quotes(t_main *main, t_splitcmd *s_cmd);
int					make_split_cmd(t_main *main, t_splitcmd *s_cmd);
int					cmd_len(t_main *main);
char				*make_temp_file(int *fd);
void				reset_here_doc(t_cmd *cmd);
char				*add_nl(char *str);
void				find_doller(char *str);
void				make_temp(t_main *main, t_cmd *cmd, char *str);
int					error_code_here_doc(t_cmd *cmd, int code);
void				eof_doller_recover(char *str);
int					recive_here_doc(t_main *main, t_cmd *cmd, char *name);
void				outfile_make(t_cmd *cmd, char *name, int append);
int					infile_make(t_main *main, t_cmd *cmd, char *str);
void				free_name(char *name, char *name2);
int					here_doc_single_re(t_main *main, t_cmd *cmd, char *name,
						char *name2);
int					here_doc_re(t_main *main, t_cmd *cmd, char *name,
						char *name2);
char				*make_name(t_main *main, int now);
int					check_here_doc(t_main *main, t_cmd *cmd, int now, int add);
char				*re_moveq(char *s);
void				default_set_cmd(t_cmd *cmd);
void				free_node_fail(t_cmd *cmd);
void				cmd_making(t_main *main, t_cmd *send, int now, int add);
int					is_opn(char *str);
void				do_echo(char **cmd);
int					get_pwd(t_main *main, char *cmd);
void				print_two_error(char *cmd1, char *cmd2, char *message);
int					error_check_syn(int syn, int pre);
int					error_message_token(char **cmd, int i);
int					error_message_syn(int pre, int i);
int					do_env_error(t_main *main, char *key);
int					cmdlist_num(t_cmd *lst);
void				print_error(char *cmd, char *message);
void				do_exit_process(t_main *main);
void				cmd_exit_process(t_main *main);
int					envplist_num(t_envp *lst);
char				**make_envp_arr(t_envp *lst);
char				*join_path(char *path, char *cmd);
int					check_cmd_path(t_envp *envp, t_cmd *cmd);
int					cmd_path(t_main *main, t_cmd *cmd);
char				*ascii_env(char *s);
char				*daller_env(int c);
char				*get_env(t_envp *env, char *str);
char				*get_g_exit_code(char *temp2);
char				*join_env_end(char *temp, char *env, char *temp2);
t_envp				*make_envpnode(char *key, char *value);
void				add_envpnode(t_envp **envp, t_envp *new);
int					check_already_add(t_main *main, char *key, char *value);
int					check_envsyn_error(char *key, char *value);
int					make_envp(t_main *main, char *arr);
int					check_num(char *num);
int					exit_num(char **cmd);
int					get_envplen(char **arr);
void				free_strlist(char **cmd);
void				cmd_free(t_main *main);
int					duble_len(char **str);
int					is_num(char *str);
int					is_alnum_str(char *str);
int					free_split(char **tmp);
void				free_cmdlist(char **cmd);
void				syntax(int *syn, char *str);
int					check_syntax(char **cmd);
void				sigint_handler(void);
void				sigquit_handler(int signum);
int					check_key_able(char *str);
int					check_while(t_envp *list, char *key, char *value);
void				set_main_env(t_main *main, t_envp *env);
int					set_input(t_main *main, t_cmd *cmd);
int					set_output(t_cmd *cmd);
void				close_multiple_fd(t_main *main, t_cmd *cmd);
void				cmd_sig_handler(int signum);
void				here_doc_sigint_handler(int signum);
void				here_doc_sigquit_handler(int signum);
void				sig_init(int option);
int					check_cmd(t_main *main, t_cmd *cmd);
int					do_cmd_set(t_main *main, t_cmd *cmd);
int					do_cmd(t_main *main);
int					do_builtin(t_cmd *list, t_main *main);
int					check_builtin(t_cmd *list);
t_pwd				set_char(t_main *main, char *path);
void				free_all(t_pwd *all);
void				save_pwd(t_main *main, char *path);
char				*q_replace(char *s);
#endif
