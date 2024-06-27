/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triple_strcmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:14:23 by somilee           #+#    #+#             */
/*   Updated: 2024/03/08 11:19:30 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	triple_strcmp(char *str, char *set)
{
	if (ft_strnstr(str, set, ft_strlen(str)))
		return (1);
	return (0);
}

int	triple_char(char *str)
{
	if (triple_strcmp(str, "<<<") == 1)
		return (1);
	if (triple_strcmp(str, ">>>") == 1)
		return (1);
	if (triple_strcmp(str, "||") == 1)
		return (1);
	return (0);
}

void	eof_doller(char *str)
{
	char	*need;
	int		i;

	i = 2;
	need = 0;
	need = ft_strnstr(str, "<<", ft_strlen(str));
	if (need)
	{
		while (need)
		{
			i = 0;
			while (need[i] && need[i] != '$')
				i++;
			while (need[i] && (!ft_isalnum(need[i]) || need[i] == '$'))
			{
				if (need[i] == '$')
					need[i] = 2;
				i++;
			}
			need = ft_strnstr(need + i, "<<", ft_strlen(need + i));
		}
	}
}

int	error_cmd(char *str)
{
	t_check	check;

	ft_bzero(&check, sizeof(t_check));
	if (q_mark(&check, str) == 1)
		return (1);
	eof_doller(str);
	if (triple_char(str) == 1)
		return (1);
	return (0);
}

int	cmd_check(char *input)
{
	if (error_cmd(input) == 1)
		return (error_message("minishell: syntax error\n", 1));
	return (0);
}
