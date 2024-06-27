/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:51:24 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 10:30:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax(int *syn, char *str)
{
	if (ft_strnstr(str, "<<", ft_strlen(str)) || ft_strnstr(str, ">>",
			ft_strlen(str)))
		*syn = HER;
	else if (*str == '<' || *str == '>')
		*syn = RED;
	else if (*str == '|')
		*syn = PIP;
	else if (*str == '$')
		*syn = DAL;
	else
		*syn = ARG;
}

int	check_syntax(char **cmd)
{
	int	pre;
	int	syn;
	int	i;

	i = 0;
	syn = FIR;
	pre = FIR;
	while (cmd[i])
	{
		syntax(&syn, cmd[i]);
		if (error_check_syn(syn, pre) == 1)
			return (error_message_token(cmd, i));
		pre = syn;
		i++;
	}
	if (pre == PIP || pre == RED || pre == HER)
		return (error_message_syn(pre, i));
	return (0);
}

void	sigint_handler(void)
{
	rl_replace_line("", 1);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
	g_exit_code = 1;
}

void	sigquit_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	set_main_env(t_main *main, t_envp *env)
{
	t_envp	*temp;

	temp = env;
	main->envp_list = env->next;
	free(temp);
}
