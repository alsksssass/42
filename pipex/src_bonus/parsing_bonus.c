/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:27:55 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/16 14:27:57 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	parsing(t_main *main, int argc, char **argv, char **envp)
{
	ft_bzero(main, sizeof(t_main));
	if (argc < 5)
		return (1);
	else
	{
		main->argv = argv;
		main->here_doc = check_here_doc(argv);
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

int	check_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) + 1) == 0)
		return (1);
	return (0);
}
