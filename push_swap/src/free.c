/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:19:05 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 19:20:30 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_save(t_main *main)
{
	int	i;

	i = 0;
	while (main->save[i])
		free(main->save[i++]);
	free(main->save);
}

int	free_malloc(t_main *main, int num)
{
	t_stack	*save;

	while (main->b_head)
		p_ab(main, pa);
	save = main->a_head;
	if (save)
	{
		while (main->a_head)
		{
			p_ab(main, pb);
			if (!(main->b_head))
				break ;
			free(main->b_head);
			main->b_head = 0;
		}
	}
	if (main->sort)
		free(main->sort);
	if (main->save)
		free_save(main);
	return (num);
}
