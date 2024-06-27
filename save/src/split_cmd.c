/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 00:18:10 by somilee           #+#    #+#             */
/*   Updated: 2024/03/04 16:07:29 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_cmd(t_main *main)
{
	t_splitcmd	s_cmd;

	ft_bzero(&s_cmd, sizeof(t_splitcmd));
	main->cmd = ft_calloc(sizeof(char *), (ft_strlen(main->input) + 1));
	make_split_cmd(main, &s_cmd);
	if (ft_strlen(main->cmd[s_cmd.i]) == 0)
	{
		free(main->cmd[s_cmd.i]);
		main->cmd[s_cmd.i] = 0;
	}
	return (0);
}

int	cmd_len(t_main *main)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = main->cmd;
	while (cmd[i])
	{
		i++;
	}
	return (i);
}

char	*make_temp_file(int *fd)
{
	int		i;
	char	*path;
	char	*name;
	char	*num;

	i = 0;
	path = "./.temp";
	while (1)
	{
		num = ft_itoa(i);
		name = ft_strjoin(path, num);
		free(num);
		*fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0666);
		if (*fd != -1)
			break ;
		free(name);
		i++;
	}
	return (name);
}

void	reset_here_doc(t_cmd *cmd)
{
	unlink(cmd->here_doc);
	free(cmd->here_doc);
	cmd->here_doc_fd = 0;
	cmd->here_doc = 0;
}

char	*add_nl(char *str)
{
	char	*send;

	send = ft_strjoin(str, "\n");
	free(str);
	return (send);
}
