/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_doller.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:19:39 by somilee           #+#    #+#             */
/*   Updated: 2024/03/01 01:45:37 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_doller(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == 2)
			*str = '$';
		str++;
	}
}

void	make_temp(t_main *main, t_cmd *cmd, char *str)
{
	char	*msg;
	size_t	size_name;
	char	*end;

	find_doller(str);
	end = ft_strtrim(str, "\'\"");
	size_name = ft_strlen(end);
	while (1)
	{
		msg = readline("> ");
		if (size_name == ft_strlen(msg))
		{
			if (ft_strncmp(end, msg, size_name) == 0)
				break ;
		}
		if (!msg)
			break ;
		if (str && !(*str == '\'' || *str == '\"'))
			msg = replace_cmd(main, msg);
		msg = add_nl(msg);
		write(cmd->here_doc_fd, msg, ft_strlen(msg));
	}
	close(cmd->here_doc_fd);
	free(end);
	exit(0);
}

void	here_doc_sigint_handler(int signum)
{
	printf("\n");
	(void)signum;
	exit(2);
}

void	here_doc_sigquit_handler(int signum)
{
	printf("\n");
	(void)signum;
	exit(1);
}

int	error_code_here_doc(t_cmd *cmd, int code)
{
	int	ret;

	ret = 0;
	if (code == 512)
	{
		ft_putstr_fd("\n", 1);
		reset_here_doc(cmd);
		ret = 1;
	}
	sig_init(INIT);
	return (ret);
}
