/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:16:22 by somilee           #+#    #+#             */
/*   Updated: 2024/03/09 17:35:02 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf(" no.%d = %c\n", i, str[i]);
		i++;
	}
}

int	check_mark(char input)
{
	char	*split_mark;

	split_mark = "|<>";
	while (*split_mark)
	{
		if (*split_mark == input)
			return (1);
		if (input == 0)
			return (0);
		split_mark++;
	}
	return (0);
}

int	continuous_check_mark(t_main *main, t_splitcmd *s_cmd)
{
	if (s_cmd->first == 0 && check_mark(main->input[s_cmd->j]) != 0
		&& s_cmd->m == 0)
	{
		main->cmd[s_cmd->i][s_cmd->k++] = main->input[s_cmd->j++];
		while (main->input[s_cmd->j] == main->input[s_cmd->j - 1])
			main->cmd[s_cmd->i][s_cmd->k++] = main->input[s_cmd->j++];
		s_cmd->i++;
		s_cmd->k = 0;
		return (0);
	}
	return (1);
}

int	space_between_quotes(t_main *main, t_splitcmd *s_cmd)
{
	if (s_cmd->first == 1 && (check_mark(main->input[s_cmd->j]) != 0
			|| main->input[s_cmd->j] == ' ' || main->input[s_cmd->j] == '\t')
		&& s_cmd->m == 0)
	{
		s_cmd->i++;
		s_cmd->k = 0;
		s_cmd->first = 0;
		return (0);
	}
	return (1);
}

int	make_split_cmd(t_main *main, t_splitcmd *s_cmd)
{
	while (main->input[s_cmd->j])
	{
		if (main->cmd[s_cmd->i] == NULL)
			main->cmd[s_cmd->i] = (char *)ft_calloc(sizeof(char),
					(ft_strlen(main->input) + 1));
		while ((main->input[s_cmd->j] == ' ' || main->input[s_cmd->j] == '\t')
			&& s_cmd->first == 0 && s_cmd->m == 0)
			s_cmd->j++;
		if (!main->input[s_cmd->j])
			break ;
		if (continuous_check_mark(main, s_cmd) == 0)
			continue ;
		s_cmd->first = 1;
		if (space_between_quotes(main, s_cmd) == 0)
			continue ;
		if ((main->input[s_cmd->j] == '\'' || main->input[s_cmd->j] == '\"') \
				&& s_cmd->m == 0)
			s_cmd->m = main->input[s_cmd->j];
		else if (s_cmd->m != 0 && s_cmd->m == main->input[s_cmd->j])
			s_cmd->m = 0;
		main->cmd[s_cmd->i][s_cmd->k++] = main->input[s_cmd->j++];
	}
	return (0);
}
