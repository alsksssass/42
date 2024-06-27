/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_fuc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:50:21 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/01 01:50:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_num(char *num)
{
	if (*num == '-')
		num++;
	if (is_num(num) == 1)
	{
		print_two_error("exit", num, "numeric argument required");
		return (255);
	}
	if (ft_strlen(num) > 19)
	{
		print_two_error("exit", num, "numeric argument required");
		return (255);
	}
	return (0);
}

int	exit_num(char **cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (cmd[1])
	{
		i = check_num(cmd[1]);
		if (i == 0)
			i = ft_atoi(cmd[1]);
	}
	if (duble_len(cmd) > 2)
	{
		print_error(cmd[0], "too many arguments");
		return (1);
	}
	exit(i);
}

int	get_envplen(char **arr)
{
	int	cnt;

	cnt = 0;
	while (*arr++)
		cnt++;
	return (cnt);
}

void	free_strlist(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = 0;
		i++;
	}
}

void	cmd_free(t_main *main)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	cmd = main->cmd_list;
	temp = 0;
	while (cmd)
	{
		free(temp);
		temp = 0;
		free(cmd->infile);
		cmd->infile = 0;
		free(cmd->outfile);
		cmd->outfile = 0;
		free_strlist(cmd->cmd);
		unlink(cmd->here_doc);
		free(cmd->here_doc);
		cmd->here_doc = 0;
		temp = cmd;
		cmd = cmd->next;
	}
	free(temp);
	main->cmd_list = 0;
}
