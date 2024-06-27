/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:44:04 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/01 01:44:05 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envplist_num(t_envp *lst)
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

char	**make_envp_arr(t_envp *lst)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = ft_calloc(sizeof(char **), (envplist_num(lst) + 1));
	i = 0;
	while (lst)
	{
		envp[i] = ft_calloc(sizeof(char *), ft_strlen(tmp) + 1);
		tmp = ft_strjoin(lst->key, "=");
		envp[i] = ft_strjoin(tmp, lst->value);
		free(tmp);
		i++;
		lst = lst->next;
	}
	return (envp);
}

char	*join_path(char *path, char *cmd)
{
	char	*tmp;

	tmp = path;
	path = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = path;
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

int	check_cmd_path(t_envp *envp, t_cmd *cmd)
{
	int		i;
	char	**path;

	while (envp)
	{
		if (ft_strncmp(envp->key, "PATH", 5) == 0)
		{
			path = ft_split(envp->value, ':');
			i = -1;
			while (path[++i])
			{
				path[i] = join_path(path[i], cmd->cmd[0]);
				if (access(path[i], X_OK) == 0)
				{
					free(cmd->cmd[0]);
					cmd->cmd[0] = ft_strdup(path[i]);
					free_cmdlist(path);
					return (0);
				}
			}
			free_cmdlist(path);
		}
		envp = envp->next;
	}
	return (1);
}

int	cmd_path(t_main *main, t_cmd *cmd)
{
	t_envp	*envp;

	envp = main->envp_list;
	if (cmd->cmd[0] && ft_strchr(cmd->cmd[0], '/'))
	{
		if (access(cmd->cmd[0], F_OK) == 0)
			print_error(cmd->cmd[0], "Permission denied");
		else
			print_error(cmd->cmd[0], "No such file or directory");
		return (1);
	}
	if (check_cmd_path(envp, cmd) == 0)
		return (0);
	print_error(cmd->cmd[0], "command not found");
	return (1);
}
