/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_single_re.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:23:45 by somilee           #+#    #+#             */
/*   Updated: 2024/03/09 13:43:45 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_single_re(t_main *main, t_cmd *cmd, char *name, char *name2)
{
	if (*name == '<')
	{
		if (infile_make(main, cmd, name2) == 1)
		{
			free_name(name, name2);
			return (1);
		}
	}
	else if (main->read_error == 0)
		outfile_make(cmd, name2, 0);
	return (0);
}

int	here_doc_re(t_main *main, t_cmd *cmd, char *name, char *name2)
{
	if (ft_strlen(name) == 2)
	{
		if (ft_strncmp(name, "<<", 3) == 0)
		{
			if (recive_here_doc(main, cmd, name2) == 1)
				return (1);
		}
		else if (ft_strncmp(name, ">>", 3) == 0 && main->read_error == 0)
			outfile_make(cmd, name2, 1);
	}
	else if (ft_strlen(name) == 1)
	{
		if (here_doc_single_re(main, cmd, name, name2) == 1)
		{
			main->read_error = 1;
			return (1);
		}
	}
	return (0);
}

char	*make_name(t_main *main, int now)
{
	char	*send;

	send = re_ascii(main->cmd[now + 1], 1);
	if (ft_strncmp(send, "\"\"", 3) == 0)
	{
		free(send);
		send = ft_strdup("");
	}
	return (send);
}

int	check_here_doc(t_main *main, t_cmd *cmd, int now, int add)
{
	char	*name;
	char	*name2;

	while (now < add)
	{
		name = re_ascii(main->cmd[now], 0);
		if (main->cmd[now + 1] && !ft_strnstr(name, "<<", ft_strlen(name)))
			name2 = make_name(main, now);
		else if (name && ft_strnstr(name, "<<", ft_strlen(name)))
			name2 = ft_strdup(main->cmd[now + 1]);
		else
			name2 = 0;
		if (name && ft_strcmp(name, "<>") == 1)
		{
			if (here_doc_re(main, cmd, name, name2) == 1)
			{
				free_name(name, name2);
				return (1);
			}
		}
		now++;
		free_name(name, name2);
	}
	return (0);
}

char	*re_moveq(char *s)
{
	char	**str;
	char	*temp;
	char	*temp2;
	char	**save;

	str = ft_split_set(s, "\"\'");
	save = str;
	if (!str)
		return (ft_strdup(s));
	temp = *str;
	while (str && *str)
	{
		str++;
		temp2 = temp;
		temp = ft_strjoin(temp, *str);
		free(temp2);
		free(*str);
	}
	free(save);
	return (temp);
}
