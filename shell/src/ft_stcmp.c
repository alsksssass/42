/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stcmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:25:38 by somilee           #+#    #+#             */
/*   Updated: 2024/03/01 01:46:03 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stcmp(char s1, char *s2)
{
	unsigned char	u1;
	unsigned char	*u2;
	unsigned int	i;

	u1 = (unsigned char)s1;
	u2 = (unsigned char *)s2;
	i = 0;
	while (u2[i])
	{
		if (u1 == (u2[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1)
		return (1);
	while (*s1)
	{
		if (ft_stcmp(*s1, s2) == 1)
			return (1);
		s1++;
	}
	return (0);
}

void	in_mark(t_check *cmd)
{
	if (cmd->here_doc_mark == 0)
		cmd->here_doc_mark = 1;
	else if (cmd->here_doc_mark == 1)
		cmd->here_doc_mark = 2;
	else if (cmd->here_doc_mark == 2)
	{
		cmd->here_doc_mark = -1;
		cmd->error = 1;
	}
}

void	out_mark(t_check *cmd)
{
	if (cmd->re_direction_mark == 0)
		cmd->re_direction_mark = 1;
	else if (cmd->re_direction_mark == 1)
		cmd->re_direction_mark = 2;
	else if (cmd->re_direction_mark == 2)
	{
		cmd->re_direction_mark = -1;
		cmd->error = 1;
	}
}

void	here_doc(t_check *cmd, char mark)
{
	if (mark == '<')
		in_mark(cmd);
	if (mark == '>')
		out_mark(cmd);
}
