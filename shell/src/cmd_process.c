/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:40:40 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 10:30:23 by sabyun           ###   ########.fr       */
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
	char	*temp;

	temp = ft_itoa(WTERMSIG(main->exit_state));
	if (WTERMSIG(main->exit_state) == 3)
	{
		g_exit_code = 131;
		ft_putstr_fd("Quit: ", 2);
		ft_putstr_fd(temp, 2);
		free(temp);
		temp = 0;
	}
	else
		g_exit_code = 130;
	ft_putstr_fd("\n", 2);
	free(temp);
}

void	cmd_exit_process(t_main *main)
{
	while (wait(&main->exit_state) > 0)
		;
	if ((WIFSIGNALED(main->exit_state)))
		do_exit_process(main);
	else
		g_exit_code = WEXITSTATUS(main->exit_state);
	dup2(main->std[0], 0);
	dup2(main->std[1], 1);
	sig_init(INIT);
}
