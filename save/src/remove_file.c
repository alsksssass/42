/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:41:03 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/07 19:30:14 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_file(char *here_doc)
{
	if (!here_doc)
		return ;
	else
	{
		unlink(here_doc);
		free(here_doc);
		here_doc = 0;
	}
}

int	go_home(t_main *main)
{
	char	*path;

	path = get_env(main->envp_list, ft_strdup("HOME"));
	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	chdir(path);
	free(path);
	return (0);
}
