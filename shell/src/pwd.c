/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:55:32 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/01 05:03:03 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pwd	set_char(t_main *main, char *path)
{
	t_pwd	send;

	ft_bzero(&send, sizeof(t_pwd));
	send.w_pwd = ft_strdup("PWD");
	send.w_old = ft_strdup("OLDPWD");
	send.w_path = ft_strdup(path);
	send.old_pwd = get_env(main->envp_list, ft_strdup(send.w_pwd));
	return (send);
}

void	free_all(t_pwd *all)
{
	free(all->w_pwd);
	free(all->w_old);
	free(all->w_path);
	free(all->old_pwd);
}

void	save_pwd(t_main *main, char *path)
{
	t_pwd	all;

	all = set_char(main, path);
	if (check_already_add(main, all.w_old, all.old_pwd) == 1)
	{
		all.w_old = 0;
		all.old_pwd = 0;
	}
	if (check_already_add(main, all.w_pwd, all.w_path) == 1)
	{
		all.w_pwd = 0;
		all.w_path = 0;
	}
	if (main->save_pwd)
		free(main->save_pwd);
	main->save_pwd = ft_strdup(path);
	free_all(&all);
}
