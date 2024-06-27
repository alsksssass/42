/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:47 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/16 14:48:32 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parsing(t_main *main, int argc, char **argv, char **envp)
{
	ft_bzero(main, sizeof(t_main));
	if (argc != 5)
	{
		ft_putstr_fd("Argument number error!!\n", 2);
		return (1);
	}
	else
	{
		main->argv = argv;
		main->here_doc = 0;
		if (main->here_doc == 1)
			main->file_name = "./.temp.txt";
		else
			main->file_name = argv[1];
		main->argc = argc;
		main->envp = envp;
		main->path = get_path(main);
		main->c_cmd = argc - (3 + main->here_doc);
	}
	return (0);
}

char	**get_path(t_main *main)
{
	char	**save;
	char	**send;
	int		path;
	int		i;

	i = 0;
	save = main->envp;
	send = 0;
	while (save[i])
	{
		path = ft_strncmp(save[i], "PATH=", 5);
		if (path == 0)
			break ;
		i++;
	}
	send = ft_split(save[i] + 5, ':');
	return (send);
}
