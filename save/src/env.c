/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:42:05 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 15:20:20 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_env(t_main *main, char *key)
{
	char	*s_key;

	s_key = ft_strdup(key);
	if (check_envsyn_error(s_key, 0) == 1)
		return (2);
	if (do_env_error(main, key) == 1)
	{
		free(s_key);
		return (1);
	}
	free(s_key);
	return (0);
}

int	check_key_able(char *str)
{
	if (ft_isdigit(*str) == 1 || !str)
	{
		ft_putstr_fd("minishell: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (*str)
	{
		if (!(ft_isalnum(*str) == 1 || *str == '_'))
		{
			ft_putstr_fd("minishell: '", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		str++;
	}
	return (0);
}

int	check_while(t_envp *list, char *key, char *value)
{
	while (list)
	{
		if (ft_strncmp(list->key, key, ft_strlen(list->key) + 1) == 0)
		{
			if (value)
			{
				free(list->value);
				list->value = ft_strdup(value);
			}
			free(key);
			free(value);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void	defult_envp(t_main *main)
{
	char	**envp;
	int		i;

	i = 0;
	envp = main->envp;
	while (envp[i])
	{
		make_envp(main, envp[i]);
		i++;
	}
}

void	print_envp(t_main *main, int env)
{
	t_envp	*envp;

	envp = main->envp_list;
	while (envp)
	{
		if (env == 0 && !envp->value)
			printf("declare -x %s\n", envp->key);
		if (env == 0 && envp->value)
			printf("declare -x %s=\"%s\"\n", envp->key, envp->value);
		if (env == 1 && envp->value)
			printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
}
