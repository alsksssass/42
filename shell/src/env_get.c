/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:42:48 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 10:30:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_str(char *str, int set)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && str[i] != set)
		i++;
	return (ft_substr(str, 0, i));
}

char	*until_daller(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	return (&str[i]);
}

char	*after_make_str(t_main *main, char *str)
{
	char	*env;
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	env = until_daller(str);
	i = 1;
	if (*env == '$')
	{
		while (env[i] && (ft_isalnum(env[i]) == 1 || env[i] == '_'))
			i++;
	}
	if ((env + i) - (str + ft_strlen(str)) > 0)
		return (ft_strdup(str));
	temp = ft_substr(str, 0, env - str);
	temp2 = make_str(env + i, 0);
	if (temp2 && ft_strncmp(temp2, "?", 1) == 0)
	{
		temp2 = get_g_exit_code(temp2);
		env = 0;
	}
	else
		env = get_env(main->envp_list, ft_substr(env, 1, i - 1));
	return (join_env_end(temp, env, temp2));
}

char	*ret_daller_env(char *str)
{
	char	*ret;

	ret = str;
	while (str && *str)
	{
		if (*str == 4)
			*str = '$';
		str++;
	}
	return (ret);
}

char	*replace_cmd(t_main *main, char *cmd)
{
	char	*mark;
	char	*send;

	send = 0;
	mark = ft_strchr(cmd, '\"');
	if (mark)
	{
		send = after_make_str(main, cmd);
		if (ft_strnstr(send, "\"\"", ft_strlen(send)))
			send = q_replace(send);
	}
	else
	{
		mark = ft_strchr(cmd, '$');
		if (mark)
			send = after_make_str(main, cmd);
		else
			send = ft_strdup(cmd);
	}
	if (ft_strchr(send, '$'))
		send = replace_cmd(main, send);
	free(cmd);
	return (ret_daller_env(send));
}
