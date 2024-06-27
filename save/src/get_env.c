/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:46:27 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/13 20:15:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ascii_env(char *s)
{
	char	*str;
	char	*ret;

	str = ft_strdup(s);
	ret = str;
	while (*str)
	{
		if (*str == '\"')
			*str = 127;
		if (*str == '\'')
			*str = 1;
		str++;
	}
	return (ret);
}

char	*daller_env(int c)
{
	char	*ret;
	char	*str;

	ret = ft_strdup("$");
	str = ret;
	while (*str)
	{
		if (*str == '$')
			*str = c;
		str++;
	}
	return (ret);
}

char	*get_env(t_envp *env, char *str)
{
	if (!*str)
	{
		free(str);
		return (daller_env(4));
	}
	while (env)
	{
		if (ft_strncmp(env->key, str, ft_strlen(str) + 1) == 0)
		{
			if (!env->value)
			{
				free(str);
				str = 0;
				return (0);
			}
			free(str);
			str = 0;
			return (ascii_env(env->value));
		}
		env = env->next;
	}
	free(str);
	return (0);
}

char	*get_g_exit_code(t_main *main, char *temp2)
{
	char	*temp;
	char	*send;

	temp = ft_substr(temp2, 1, ft_strlen(temp2 + 1));
	free(temp2);
	temp2 = ft_itoa(main->exit_code);
	send = ft_strjoin(temp2, temp);
	free(temp2);
	free(temp);
	return (send);
}

char	*join_env_end(char *temp, char *env, char *temp2)
{
	char	*send;

	send = ft_strjoin(temp, env);
	free(temp);
	free(env);
	env = send;
	send = ft_strjoin(env, temp2);
	free(env);
	free(temp2);
	return (send);
}
