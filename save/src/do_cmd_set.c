/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:53:36 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/14 15:31:20 by sabyun           ###   ########.fr       */
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
		if (cmd->error_infile > 0)
		{
			open(cmd->infile, O_RDONLY);
			return (ret_msg(cmd->infile, strerror(errno), 1));
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
		if (cmd->error_outfile > 0)
		{
			open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			return (ret_msg(cmd->outfile, strerror(errno), 1));
		}
		dup2(cmd->outfile_fd, 1);
	}
	close(cmd->outfile_fd);
	return (0);
}

void	cmd_sig_handler(int signum)
{
	write(1, "\n", 1);
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

	if (!cmd->cmd[0])
		return (0);
	if (cmd->cmd[0] && ft_strchr(cmd->cmd[0], '/'))
		return (relative_absolute_path(cmd->cmd[0]));
	if (cmd_path(main, cmd) == 1)
		return (127);
	if (stat(cmd->cmd[0], &buf) != 0)
		return (127);
	if (S_ISDIR(buf.st_mode))
	{
		print_error(cmd->cmd[0], "command not found");
		return (127);
	}
	return (0);
}
