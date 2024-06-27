/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:59:24 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 10:30:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_main *main, int end)
{
	free(main->input);
	main->input = 0;
	free_cmdlist(main->cmd);
	main->cmd = 0;
	if (end == 1)
	{
		free_cmdlist(main->path);
		free(main->save_pwd);
	}
	cmd_free(main);
}

int	split_make_cmd(t_main *main)
{
	if (split_cmd(main) != 0)
	{
		g_exit_code = 258;
		free_cmd(main, 0);
		return (1);
	}
	if (check_syntax(main->cmd) == 1)
	{
		g_exit_code = 258;
		free_cmd(main, 0);
		return (1);
	}
	if (make_cmd(main) == 1)
	{
		g_exit_code = 1;
		free_cmd(main, 0);
		return (1);
	}
	return (0);
}

void	do_minishell(t_main *main)
{
	while (1)
	{
		main->input = readline("minishell: ");
		if (!main->input)
		{
			printf("exit\n");
			break ;
		}
		if (*main->input == 0)
			continue ;
		add_history(main->input);
		if (cmd_check(main->input) == 1)
		{
			g_exit_code = 258;
			free(main->input);
			continue ;
		}
		main->input = replace_cmd(main, main->input);
		if (split_make_cmd(main) == 1)
			continue ;
		do_cmd(main);
		sig_init(INIT);
		free_cmd(main, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_main	main;

	(void)argc;
	(void)argv;
	ft_bzero(&main, sizeof(t_main));
	main.envp = envp;
	main.fd_tmp = -1;
	main.std[0] = dup(STDIN_FILENO);
	main.std[1] = dup(STDOUT_FILENO);
	g_exit_code = main.exit_state;
	defult_envp(&main);
	sig_init(INIT);
	do_minishell(&main);
	free_cmd(&main, 1);
	clear_history();
	close(main.std[0]);
	close(main.std[1]);
	return (0);
}
