/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qq_note.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:11:01 by somilee           #+#    #+#             */
/*   Updated: 2024/03/02 15:58:27 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qq_note(t_check *cmd)
{
	if (cmd->qq_mark == 1)
		cmd->qq_mark = 0;
	else if (cmd->qq_mark == 0)
		cmd->qq_mark = 1;
}

void	q_note(t_check *cmd)
{
	if (cmd->q_mark == 1)
		cmd->q_mark = 0;
	else if (cmd->q_mark == 0)
		cmd->q_mark = 1;
}

void	q_swap(t_check *cmd, char *mark, int i)
{
	if (mark[i] == '\'' && cmd->qq_mark == 1)
		mark[i] = 1;
	if (mark[i] == '|' && (cmd->qq_mark == 1 || cmd->q_mark == 1))
		mark[i] = 6;
	if (mark[i] == '<' && (cmd->qq_mark == 1 || cmd->q_mark == 1))
		mark[i] = 5;
	if (mark[i] == '>' && (cmd->qq_mark == 1 || cmd->q_mark == 1))
		mark[i] = 2;
	if (mark[i] == '\"' && cmd->q_mark == 1)
		mark[i] = 127;
	if (mark[i] == '$' && cmd->q_mark == 1)
		mark[i] = 3;
}

int	q_mark(t_check *cmd, char *mark)
{
	int	i;

	i = 0;
	while (mark[i])
	{
		if (mark[i] == '\"' && cmd->q_mark != 1)
			qq_note(cmd);
		if (mark[i] == '\'' && cmd->qq_mark != 1)
			q_note(cmd);
		if (cmd->q_mark == 1 || cmd->qq_mark == 1)
			q_swap(cmd, mark, i);
		i++;
	}
	if (cmd->qq_mark == 1 || cmd->q_mark == 1)
		return (1);
	return (0);
}

int	error_message(char *str, int error_num)
{
	ft_putstr_fd(str, 2);
	return (error_num);
}
