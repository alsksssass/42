/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inoutfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:34:09 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/16 20:56:45 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_do(t_cmd *cmd)
{
	if (cmd->error_infile > 0)
	{
		open(cmd->infile, O_RDONLY);
		perror("minishell");
		return (1);
	}
	dup2(cmd->infile_fd, 0);
	close(cmd->infile_fd);
	return (0);
}

int	outfile_do(t_cmd *cmd)
{
	if (cmd->error_outfile > 0)
	{
		open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		perror("minishell");
		return (1);
	}
	dup2(cmd->outfile_fd, 1);
	close(cmd->outfile_fd);
	return (0);
}

int	do_fd(t_cmd *cmd, int option)
{
	if (option == 1)
	{
		if (outfile_do(cmd) == 1)
			return (1);
		if (infile_do(cmd) == 1)
			return (1);
	}
	else
	{
		if (infile_do(cmd) == 1)
			return (1);
		if (outfile_do(cmd) == 1)
			return (1);
	}
	return (0);
}

int	do_mfd(t_main *main, t_cmd *cmd, int option)
{
	if (option == 2)
	{
		if (set_output(cmd) == 1)
			return (1);
		if (set_input(main, cmd) == 1)
			return (1);
	}
	else
	{
		if (set_input(main, cmd) == 1)
			return (1);
		if (set_output(cmd) == 1)
			return (1);
	}
	return (0);
}

char	*join_srt(char *s1, char *s2)
{
	char	*temp;
	char	*send;

	temp = ft_strjoin(s1, "/");
	send = ft_strjoin(temp, s2);
	free(temp);
	return (send);
}
