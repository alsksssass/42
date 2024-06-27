/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:25:55 by somilee           #+#    #+#             */
/*   Updated: 2024/03/02 14:02:29 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*to_char_op(char *s)
{
	char	*temp;
	char	*temp2;

	temp = re_moveq(s);
	temp2 = temp;
	while (temp && *temp)
	{
		if (*temp == 1)
			*temp = '\'';
		if (*temp == 3)
			*temp = '$';
		if (*temp == 127)
			*temp = '\"';
		if (*temp == 6)
			*temp = '|';
		if (*temp == 5)
			*temp = '<';
		if (*temp == 2)
			*temp = '>';
		temp++;
	}
	return (temp2);
}

char	*re_ascii(char *s, int option)
{
	char	*str;

	if (option == 0)
		str = to_char_nomal(s);
	else
		str = to_char_op(s);
	return (str);
}

void	default_set_cmd(t_cmd *cmd)
{
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->here_doc_fd = -1;
}

void	free_node_fail(t_cmd *cmd)
{
	if (cmd->infile)
		unlink(cmd->infile);
	if (cmd->here_doc)
		unlink(cmd->infile);
}

void	cmd_making(t_main *main, t_cmd *send, int now, int add)
{
	int	i;

	i = 0;
	while (now < add)
	{
		if (ft_strcmp(main->cmd[now], "|<>") == 0)
		{
			send->cmd[i] = re_ascii(main->cmd[now], 1);
			if (ft_strncmp(send->cmd[i], "\"\"", 3) == 0)
			{
				free(send->cmd[i]);
				send->cmd[i] = ft_strdup("");
			}
			i++;
		}
		else
			now++;
		now++;
	}
}
