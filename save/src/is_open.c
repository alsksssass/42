/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:33:57 by somilee           #+#    #+#             */
/*   Updated: 2024/03/09 18:09:40 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_opn(char *str)
{
	if (*str != '-')
		return (1);
	str++;
	if (!*str)
		return (1);
	while (str && *str)
	{
		if (!(*str == 'n'))
			return (1);
		str++;
	}
	return (0);
}

void	do_echo(char **cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (1)
	{
		if (ft_strlen(cmd[i]) != 0 && is_opn(cmd[i]) == 0)
		{
			option = 1;
			i++;
		}
		else
			break ;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i])
			ft_putstr_fd(" ", 1);
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}

int	echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd)
		return (0);
	if (!cmd[i])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	do_echo(cmd);
	return (0);
}

int	pwd(t_main *main)
{
	char	path[4096];

	if (getcwd(path, sizeof(path)))
		printf("%s\n", path);
	else if (main->save_pwd)
	{
		ft_putstr_fd(main->save_pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		print_error("getcwd", "cannot access parent directories");
		return (1);
	}
	return (0);
}

int	get_pwd(t_main *main, char *cmd)
{
	char	*old_pwd;
	char	pwd[4096];

	old_pwd = 0;
	if (getcwd(pwd, sizeof(pwd)))
		old_pwd = join_srt(pwd, cmd);
	else
		old_pwd = ft_strdup(main->save_pwd);
	if (chdir(old_pwd) != 0)
	{
		free(old_pwd);
		return (ret_msg(cmd, "No such file or directory", 1));
	}
	free(old_pwd);
	return (0);
}
