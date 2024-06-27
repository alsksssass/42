/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_fuc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:50:21 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/13 20:21:17 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_num(char *num)
{
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
	return (ft_atoi(num));
}

int	exit_num(t_main *main, char **cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (cmd[1] && duble_len(cmd) == 2)
		main->exit_code = check_num(cmd[1]);
	if (duble_len(cmd) > 2)
	{
		i = check_num(cmd[1]);
		if (i != 255)
		{
			print_error(cmd[0], "too many arguments");
			return (1);
		}
		main->exit_code = 255;
	}
	exit(main->exit_code);
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
		remove_file(cmd->here_doc);
		temp = cmd;
		cmd = cmd->next;
	}
	free(temp);
	main->cmd_list = 0;
}
