/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:38:40 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/01 04:59:54 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_main *main, char *cmd)
{
	char	path[4096];
	char	*old_pwd;

	if (chdir(cmd) != 0)
		if (get_pwd(main, cmd) == 1)
			return (1);
	if (getcwd(path, sizeof(path)))
		save_pwd(main, path);
	else
	{
		old_pwd = main->save_pwd;
		ft_putstr_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory\n", 2);
		main->save_pwd = ft_strjoin(main->save_pwd, "/..");
		free(old_pwd);
	}
	return (0);
}

int	unset_built(t_main *main, char **cmd)
{
	int	i;
	int	code;
	int	ret;

	ret = 0;
	code = 0;
	i = 1;
	code = 0;
	while (cmd[i])
	{
		code = delete_env(main, cmd[i]);
		if (code == 2)
			ret = 1;
		i++;
	}
	return (ret);
}

int	export_built(t_main *main, char **cmd)
{
	int	i;
	int	ret;
	int	code;

	code = 0;
	ret = 0;
	i = 1;
	if (!cmd[i])
	{
		print_envp(main, 0);
	}
	while (cmd[i])
	{
		code = make_envp(main, cmd[i]);
		if (code == 1)
			ret = 1;
		i++;
	}
	return (ret);
}

int	check_builtin(t_cmd *list)
{
	char	**cmd;

	cmd = list->cmd;
	if (!list || !cmd || !*cmd)
		return (1);
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (0);
	return (1);
}

int	do_builtin(t_cmd *list, t_main *main)
{
	char	**cmd;

	cmd = list->cmd;
	if (!list || !cmd || !*cmd)
		return (1);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (echo(cmd));
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (pwd(main));
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (cd(main, cmd[1]));
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (exit_num(cmd));
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (export_built(main, cmd));
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (unset_built(main, cmd));
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
	{
		print_envp(main, 1);
		return (1);
	}
	return (0);
}
