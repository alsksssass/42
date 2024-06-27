/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_fd_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:17:48 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/17 10:21:29 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_main *main)
{
	close(main->std[0]);
	close(main->std[1]);
}

void	fd_init(t_main *main)
{
	dup2(main->std[0], 0);
	dup2(main->std[1], 1);
}
