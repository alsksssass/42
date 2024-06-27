/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:27:48 by somilee           #+#    #+#             */
/*   Updated: 2024/03/04 10:30:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*make_node(t_main *main, int now, int add)
{
	t_cmd	*send;

	send = ft_calloc(sizeof(t_cmd), 1);
	default_set_cmd(send);
	if (check_here_doc(main, send, now, add) == 1)
		return (0);
	cmd_making(main, send, now, add);
	if ((!send->cmd[0] && !send->infile && !send->outfile && !send->here_doc)
		&& main->read_error == 0)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		free_node_fail(send);
		free(send);
		g_exit_code = 258;
		return (0);
	}
	return (send);
}

int	get_next(t_main *main, int num)
{
	int	i;

	i = num;
	if (num == 0)
		i = 1;
	while (main->cmd[i])
	{
		if (ft_stcmp(*main->cmd[i], "|"))
			return (i);
		i++;
	}
	return (i);
}

void	add_node(t_main *main, t_cmd *new)
{
	t_cmd	*list;

	list = main->cmd_list;
	if (!list)
	{
		main->cmd_list = new;
		return ;
	}
	while (list->next != 0)
		list = list->next;
	list->next = new;
}

char	*value_check(char *str)
{
	char	*set;
	char	*temp;

	set = 0;
	if (!str || !*str)
		return (str);
	if (*str == '\'')
		set = "\'";
	if (*str == '\"')
		set = "\"";
	if (set == 0)
		return (str);
	else
	{
		temp = str;
		set = ft_strtrim(str, set);
		free(temp);
		return (set);
	}
}

int	make_cmd(t_main *main)
{
	char	**cmd;
	t_cmd	*node;
	int		i;
	int		j;

	i = 0;
	cmd = main->cmd;
	while (cmd[i])
	{
		j = get_next(main, i);
		node = make_node(main, i, j);
		if (node == NULL)
			return (1);
		add_node(main, node);
		i = j;
		if (!cmd[i])
			break ;
		i++;
	}
	main->read_error = 0;
	return (0);
}
