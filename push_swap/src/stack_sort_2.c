/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:04:36 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 19:12:31 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pivot	pivot_set(int min, int max)
{
	t_pivot	pivot;
	int		base;

	ft_bzero(&pivot, sizeof(pivot));
	base = (max - min) / 3;
	pivot.pivot_2 = min + base * 2 + ((max - min) % 3 > 0);
	pivot.pivot_1 = min + base + ((max - min) % 3 > 1);
	pivot.pivot = min + base;
	pivot.max = max;
	pivot.min = min;
	return (pivot);
}

static int	check_big_a(t_pivot pivot, t_main *main, int *ra_count,
		int *rb_count)
{
	int	bt;

	bt = main->b_head->pre->num;
	if (bt < pivot.pivot_1)
	{
		commander(main, rb);
		(*rb_count)++;
	}
	else
	{
		if (bt >= pivot.pivot_2)
			commander(main, pa);
		else
		{
			commander(main, pa);
			commander(main, ra);
			(*ra_count)++;
		}
	}
	return (1);
}

void	push_b_to_a(t_main *main, int min, int max)
{
	int		i;
	t_pivot	pivot;
	int		ra_count;
	int		rb_count;

	ra_count = 0;
	rb_count = 0;
	i = 0;
	pivot = pivot_set(min, max);
	if (tiny_swap_to_a(main, min, max, pivot))
		return ;
	else
	{
		while (i < max - min)
		{
			if (!check_big_a(pivot, main, &ra_count, &rb_count))
				break ;
			i++;
		}
	}
	push_a_to_b(main, pivot.pivot_2, max);
	rrr_roller(main, ra_count, rb_count);
	push_a_to_b(main, pivot.pivot_1, pivot.pivot_2);
	push_b_to_a(main, min, pivot.pivot_1);
}
