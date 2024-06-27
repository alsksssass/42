/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:02:42 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 19:07:55 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rrr_roller(t_main *main, int ra_count, int rb_count)
{
	int	i;

	i = 0;
	while (i < ra_count && i < rb_count)
	{
		commander(main, rrr);
		i++;
	}
	while (i < ra_count)
	{
		commander(main, rra);
		i++;
	}
	while (i < rb_count)
	{
		commander(main, rrb);
		i++;
	}
}

static void	frist_a_to_b(t_main *main, t_pivot pivot)
{
	int	at;

	at = main->a_head->pre->num;
	if ((at) < (pivot.pivot_1))
	{
		commander(main, pb);
		commander(main, rb);
	}
	else
		commander(main, pb);
}

static int	check_big(t_pivot pivot, t_main *main, int *ra_count, int *rb_count)
{
	int	at;

	at = main->a_head->pre->num;
	if ((at) >= (pivot.pivot_2) && main->a_size > 1)
	{
		if (!(pivot.max == main->total && pivot.min == 0))
			(*ra_count)++;
		commander(main, ra);
	}
	else if (!(pivot.max == main->total && pivot.min == 0)
		&& at < pivot.pivot_2)
	{
		if ((at) >= (pivot.pivot_1))
		{
			commander(main, pb);
			commander(main, rb);
			(*rb_count)++;
		}
		else
			commander(main, pb);
	}
	else if (pivot.max == main->total && pivot.min == 0 && at < pivot.pivot_2)
		frist_a_to_b(main, pivot);
	return (1);
}

void	push_a_to_b(t_main *main, int min, int max)
{
	int		i;
	int		ra_count;
	int		rb_count;
	t_pivot	pivot;

	pivot = pivot_set(min, max);
	ra_count = 0;
	rb_count = 0;
	i = 0;
	if (max - min <= 1)
		return ;
	if (tiny_swap(main, min, max, pivot))
		return ;
	while (i < max - min)
	{
		if (!check_big(pivot, main, &ra_count, &rb_count))
			break ;
		i++;
	}
	if (!(max == main->total && min == 0))
		rrr_roller(main, ra_count, rb_count);
	push_a_to_b(main, pivot.pivot_2, max);
	push_b_to_a(main, pivot.pivot_1, pivot.pivot_2);
	push_b_to_a(main, min, pivot.pivot_1);
}
