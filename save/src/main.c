/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:59:24 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/17 10:26:04 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status;

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
		main->exit_code = 258;
		free_cmd(main, 0);
		return (1);
	}
	if (check_syntax(main->cmd) == 1)
	{
		main->exit_code = 258;
		free_cmd(main, 0);
		return (1);
	}
	if (make_cmd(main) == 1)
	{
		main->exit_code = 1;
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
		sig_check(main);
		if (!main->input)
		{
			printf("exit\n");
			break ;
		}
		if (*main->input == 0)
		{
			enter_null(main);
			continue ;
		}
		add_history(main->input);
		if (cmd_check(main->input) == 1)
		{
			free_ret(main, main->input, 258);
			continue ;
		}
		main->input = replace_cmd(main, main->input);
		if (split_make_cmd(main) == 1)
			continue ;
		end_cmd(main);
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
	defult_envp(&main);
	sig_init(INIT);
	do_minishell(&main);
	free_cmd(&main, 1);
	rl_clear_history();
	return (main.exit_code);
}
