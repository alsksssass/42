/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_doller_recover.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:21:26 by somilee           #+#    #+#             */
/*   Updated: 2024/03/13 20:11:27 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eof_doller_recover(char *str)
{
	while (*str)
	{
		if (*str == 2)
			*str = '$';
		str++;
	}
}

int	recive_here_doc(t_main *main, t_cmd *cmd, char *name)
{
	pid_t	child;
	int		code;

	code = 0;
	if (cmd->here_doc_fd != 0)
		reset_here_doc(cmd);
	cmd->here_doc = make_temp_file(&cmd->here_doc_fd);
	sig_init(IGN);
	if (!(name))
		return (1);
	eof_doller_recover(name);
	child = fork();
	if (child == 0)
	{
		sig_init(HERE);
		make_temp(main, cmd, name);
		sig_init(INIT);
	}
	close(cmd->here_doc_fd);
	wait(&code);
	return (error_code_here_doc(cmd, code));
}

void	outfile_make(t_cmd *cmd, char *name, int append)
{
	if (cmd->outfile || cmd->i == 1)
		close(cmd->outfile_fd);
	if (cmd->error_outfile == 1)
		return ;
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = 0;
	}
	cmd->outfile = ft_strdup(name);
	if (append == 1)
		cmd->outfile_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND,
				0666);
	else
		cmd->outfile_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0666);
	if (cmd->outfile_fd < 0)
		cmd->error_outfile = 1;
	if (cmd->do_num == 0)
		cmd->do_num = 2;
	cmd->append = append;
}

int	infile_make(t_main *main, t_cmd *cmd, char *str)
{
	if (cmd->infile && cmd->infile_fd == -1)
		return (0);
	if (cmd->infile)
	{
		free(cmd->infile);
		close(cmd->infile_fd);
	}
	if (!(str))
	{
		ft_putstr_fd("minishell: ambiguous redirec\n", 2);
		return (0);
	}
	cmd->infile = ft_strdup(str);
	cmd->infile_fd = open(cmd->infile, O_RDONLY);
	if (cmd->infile_fd == -1)
	{
		main->exit_code = 1;
		cmd->i = 1;
		cmd->error_infile = 1;
		main->read_error = 1;
	}
	if (cmd->do_num == 0)
		cmd->do_num = 1;
	return (0);
}

void	free_name(char *name, char *name2)
{
	free((void *)name);
	name = 0;
	free((void *)name2);
	name2 = 0;
}
