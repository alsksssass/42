/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:27:19 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/16 14:27:40 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_cmd(t_main *main, char *cmd)
{
	char	**temp;
	char	*tmp;
	char	*checker;
	int		i;

	i = 0;
	temp = main->path;
	checker = 0;
	while (temp[i])
	{
		checker = ft_strjoin(temp[i], "/");
		tmp = checker;
		checker = ft_strjoin(checker, cmd);
		if (tmp)
			free(tmp);
		if (access(checker, X_OK) == 0)
			return (checker);
		else
			free(checker);
		i++;
	}
	return (0);
}

t_cmd	cmd_checker(t_main *main, int num)
{
	t_cmd	send;

	ft_bzero(&send, sizeof(t_cmd));
	send.command = ft_split(main->argv[num + main->here_doc], ' ');
	send.path_command = send.command[0];
	if (access(send.command[0], X_OK) == 0)
		return (send);
	else
	{
		send.path_command = find_cmd(main, send.path_command);
		if (send.path_command == 0)
			error_cmd(main, 127);
	}
	return (send);
}

void	error_cmd(t_main *main, int error)
{
	if (error == 127)
		ft_putstr_fd("pipex: command not found\n", 2);
	if (error == -1 || error == -2)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		if (error == -1)
			ft_putstr_fd(main->argv[main->argc - 1], 2);
		else
			ft_putstr_fd(main->file_name, 2);
		ft_putstr_fd("\n", 2);
	}
	main->error = error;
}

void	free_malloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}
