/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:53:36 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/01 02:19:39 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_input(t_main *main, t_cmd *cmd)
{
	if (main->fd_tmp > 0)
	{
		dup2(main->fd_tmp, 0);
	}
	close(main->fd_tmp);
	if (cmd->infile)
	{
		if (cmd->infile_fd < 0)
		{
			print_error(cmd->infile, "No such file or directory");
			return (1);
		}
		dup2(cmd->infile_fd, 0);
	}
	close(cmd->infile_fd);
	if (cmd->here_doc)
	{
		cmd->here_doc_fd = open(cmd->here_doc, O_RDONLY);
		dup2(cmd->here_doc_fd, 0);
		close(cmd->here_doc_fd);
	}
	return (0);
}

int	set_output(t_cmd *cmd)
{
	if (cmd->fd[1] != -1)
	{
		dup2(cmd->fd[1], 1);
	}
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	if (cmd->outfile)
	{
		if (cmd->outfile_fd < 0)
		{
			print_error(cmd->outfile, "No such file or directory");
			return (1);
		}
		dup2(cmd->outfile_fd, 1);
	}
	close(cmd->outfile_fd);
	return (0);
}

void	cmd_sig_handler(int signum)
{
	printf("\n");
	(void)signum;
	exit(0);
}

void	close_multiple_fd(t_main *main, t_cmd *cmd)
{
	close(main->fd_tmp);
	main->fd_tmp = dup(cmd->fd[0]);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	close(cmd->infile_fd);
	close(cmd->outfile_fd);
}

int	check_cmd(t_main *main, t_cmd *cmd)
{
	struct stat	buf;

	if (access(cmd->cmd[0], X_OK) == 0)
	{
		stat(cmd->cmd[0], &buf);
		if (S_ISDIR(buf.st_mode) != 0)
		{
			print_error(cmd->cmd[0], "is a directory");
			return (126);
		}
	}
	if (access(cmd->cmd[0], X_OK) != 0)
		if (cmd_path(main, cmd) == 1)
			return (127);
	return (0);
}
