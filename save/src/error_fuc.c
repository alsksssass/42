/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fuc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:45:07 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/13 21:19:40 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_two_error(char *cmd1, char *cmd2, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	error_check_syn(int syn, int pre)
{
	if (pre == FIR || syn == FIR)
		return (0);
	if (pre == RED && (syn == RED))
		return (1);
	if (pre == PIP && (syn == PIP))
		return (1);
	return (0);
}

int	error_message_token(char **cmd, int i)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(cmd[i], 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	error_message_syn(int pre, int i)
{
	if (pre == RED && i == 1)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return (1);
	}
	ft_putstr_fd("minishell: syntax error\n", 2);
	return (1);
}

int	do_env_error(t_main *main, char *key)
{
	t_envp	*env;
	t_envp	*temp;

	env = main->envp_list;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			if (env == main->envp_list)
				set_main_env(main, env);
			else
			{
				temp->next = env->next;
				free(env->key);
				free(env->value);
				free(env);
			}
			return (1);
		}
		temp = env;
		env = env->next;
	}
	return (0);
}
