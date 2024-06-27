/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:54:02 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/01 04:39:49 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*make_envpnode(char *key, char *value)
{
	t_envp	*send;

	send = ft_calloc(sizeof(t_envp), 1);
	send->key = key;
	send->value = value;
	return (send);
}

void	add_envpnode(t_envp **envp, t_envp *new)
{
	t_envp	*list;

	if (envp == 0)
		return ;
	if (*envp == 0)
	{
		*envp = new;
		return ;
	}
	list = *envp;
	while (list->next != 0)
		list = list->next;
	list->next = new;
}

int	check_already_add(t_main *main, char *key, char *value)
{
	t_envp	*list;

	list = main->envp_list;
	if (check_key_able(key) == 1)
	{
		free(key);
		free(value);
		return (1);
	}
	if (check_while(list, key, value) == 1)
		return (1);
	return (0);
}

int	check_envsyn_error(char *key, char *value)
{
	if (ft_isdigit(*key) == 1)
	{
		ft_putstr_fd("minishell: '", 2);
		ft_putstr_fd(key, 2);
		if (value)
		{
			ft_putstr_fd("=", 2);
			ft_putstr_fd(value, 2);
		}
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		free(value);
		return (1);
	}
	return (0);
}

int	make_envp(t_main *main, char *arr)
{
	char	*str;
	char	*key;
	char	*value;

	str = ft_strchr(arr, '=');
	if (str == 0 || str == arr)
	{
		key = ft_strdup(arr);
		value = 0;
	}
	else
	{
		key = ft_substr(arr, 0, str - arr);
		value = ft_substr(arr, str - arr + 1, ft_strlen(str + 1));
		value = value_check(value);
	}
	if (check_envsyn_error(key, value) == 1)
		return (1);
	if (check_already_add(main, key, value) == 1)
		return (0);
	add_envpnode(&main->envp_list, make_envpnode(key, value));
	return (0);
}
