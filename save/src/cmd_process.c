/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:40:40 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/13 20:10:47 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmdlist_num(t_cmd *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}

void	print_error(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	do_exit_process(t_main *main)
{
	if (WTERMSIG(main->exit_state) == 3)
	{
		main->exit_code = 131;
		ft_putstr_fd("Quit: 3\n", 2);
	}
	else
	{
		main->exit_code = 130;
		printf("\n");
	}
}

void	cmd_exit_process(t_main *main, pid_t last_pid)
{
	pid_t	get;

	while (1)
	{
		get = wait(&main->exit_state);
		if (get < 0)
			break ;
		if (get == last_pid)
		{
			if ((WIFSIGNALED(main->exit_state)))
				do_exit_process(main);
			else
				main->exit_code = WEXITSTATUS(main->exit_state);
		}
	}
	dup2(main->std[0], 0);
	dup2(main->std[1], 1);
	sig_init(INIT);
}
