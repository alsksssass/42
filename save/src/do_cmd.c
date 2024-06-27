/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:41:32 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/16 21:04:03 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_builtin(t_main *main, t_cmd *cmd)
{
	main->std[0] = dup(STDIN_FILENO);
	main->std[1] = dup(STDOUT_FILENO);
	if (do_fd(cmd, cmd->do_num) == 1)
		return (1);
	main->exit_code = do_builtin(main->cmd_list, main);
	return (main->exit_code);
}

void	do_multiple_cmd(t_main *main, t_cmd *cmd)
{
	int	check_c;

	check_c = 0;
	sig_init(CMD);
	if (do_mfd(main, cmd, cmd->do_num) == 1)
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

int	multiple_cmd(t_main *main, t_cmd *cmd)
{
	cmd->child = fork();
	if (cmd->child < 0)
	{
		perror("minishell : ");
		exit(1);
	}
	if (cmd->child == 0)
		do_multiple_cmd(main, cmd);
	close_multiple_fd(main, cmd);
	return (0);
}

void	sig_init(int option)
{
	if (option == INIT)
	{
		rl_catch_signals = 0;
		signal(SIGINT, (void *)sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == CMD)
	{
		rl_catch_signals = 0;
		signal(SIGINT, cmd_sig_handler);
		signal(SIGQUIT, cmd_sig_handler);
	}
	else if (option == HERE)
	{
		rl_catch_signals = 1;
		signal(SIGINT, here_doc_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == IGN)
	{
		rl_catch_signals = 1;
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
		main->exit_code = single_builtin(main, cmd);
		fd_init(main);
		close_fd(main);
		return (0);
	}
	while (i < main->cmd_list_num)
	{
		sig_init(IGN);
		if (cmd && i + 1 < main->cmd_list_num && pipe(cmd->fd) == -1)
			return (1);
		multiple_cmd(main, cmd);
		i++;
		if (cmd->next)
			cmd = cmd->next;
	}
	cmd_exit_process(main, cmd->child);
	return (0);
}
