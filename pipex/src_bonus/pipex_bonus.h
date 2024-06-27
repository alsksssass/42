/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:28:15 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/16 14:28:20 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_main
{
	char	**argv;
	char	**envp;
	char	**path;
	char	*file_name;
	int		here_doc;
	int		state;
	int		fd[2];
	int		argc;
	int		error;
	int		o_f;
	int		w_f;
	int		c_count;
	int		w_count;
	int		c_cmd;
	int		old_fd;
}			t_main;

typedef struct s_cmd
{
	char	**command;
	char	*path_command;
	int		error;
}			t_cmd;
void		error_cmd(t_main *main, int error);
char		*find_cmd(t_main *main, char *cmd);
t_cmd		cmd_checker(t_main *main, int num);
void		error_cmd(t_main *main, int error);
void		free_malloc(char **str);
int			parsing(t_main *main, int argc, char **argv, char **envp);
char		**get_path(t_main *main);
int			check_here_doc(char **argv);
int			open_fd(t_main *main, int *fd);
int			write_fd(t_main *main);
int			nomal_fd(t_main *main, int *fd);
int			set_fd(t_main *main, int i, int *fd);
#endif
