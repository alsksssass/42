/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:41:32 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 10:30:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_builtin(t_main *main, t_cmd *cmd)
{
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
	g_exit_code = do_builtin(main->cmd_list, main);
	return (g_exit_code);
}

int	multiple_cmd(t_main *main, t_cmd *cmd)
{
	int	check_c;

	check_c = 0;
	cmd->child = fork();
	if (cmd->child == 0)
	{
		sig_init(CMD);
		if (set_input(main, cmd) == 1 || set_output(cmd) == 1)
		{
			main->exit_state = 1;
			exit(1);
		}
		if (check_builtin(cmd) == 0)
		{
			main->exit_state = do_builtin(cmd, main);
			exit(0);
		}
		check_c = check_cmd(main, cmd);
		if (check_c != 0)
			exit(check_c);
		execve(cmd->cmd[0], cmd->cmd, make_envp_arr(main->envp_list));
		exit(0);
	}
	close_multiple_fd(main, cmd);
	return (0);
}

void	sig_init(int option)
{
	if (option == INIT)
	{
		signal(SIGINT, (void *)sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == CMD)
	{
		signal(SIGINT, cmd_sig_handler);
		signal(SIGQUIT, cmd_sig_handler);
	}
	else if (option == HERE)
	{
		signal(SIGINT, here_doc_sigint_handler);
		signal(SIGQUIT, here_doc_sigquit_handler);
	}
	else if (option == IGN)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	do_cmd(t_main *main)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = main->cmd_list;
	main->cmd_list_num = cmdlist_num(cmd);
	if (main->cmd_list_num <= 1 && check_builtin(main->cmd_list) == 0)
	{
		g_exit_code = single_builtin(main, cmd);
		dup2(main->std[0], 0);
		dup2(main->std[1], 1);
		return (0);
	}
	while (i < main->cmd_list_num)
	{
		sig_init(IGN);
		if (cmd && i + 1 < main->cmd_list_num)
			if (pipe(cmd->fd) == -1)
				return (1);
		multiple_cmd(main, cmd);
		i++;
		cmd = cmd->next;
	}
	cmd_exit_process(main);
	return (0);
}
