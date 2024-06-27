/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:28:03 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/22 13:57:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_fd(t_main *main, int *fd)
{
	main->o_f = open(main->file_name, O_RDONLY);
	if (main->o_f == -1)
	{
		error_cmd(main, -2);
		return (1);
	}
	if (dup2(main->o_f, STDIN_FILENO) == -1)
		return (1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (1);
	close(main->o_f);
	if (main->here_doc == 1)
		unlink(main->file_name);
	return (0);
}

int	write_fd(t_main *main)
{
	if (main->here_doc == 0)
		main->w_f = open(main->argv[main->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		main->w_f = open(main->argv[main->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (main->w_f == -1)
	{
		error_cmd(main, -1);
		return (1);
	}
	if (dup2(main->old_fd, STDIN_FILENO) == -1)
		return (1);
	if (dup2(main->w_f, STDOUT_FILENO) == -1)
		return (1);
	close(main->w_f);
	return (0);
}

int	nomal_fd(t_main *main, int *fd)
{
	if (dup2(main->old_fd, STDIN_FILENO) == -1)
		return (1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int	set_fd(t_main *main, int i, int *fd)
{
	int	error;

	error = 0;
	if (i == 0)
		error = (open_fd(main, fd));
	else if (i == main->c_cmd - 1)
		error = (write_fd(main));
	else
		error = (nomal_fd(main, fd));
	close(fd[0]);
	close(fd[1]);
	return (error);
}
