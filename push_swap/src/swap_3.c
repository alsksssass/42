/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:17:29 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 19:18:58 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_3_1(t_main *main, int sp)
{
	if (sp == 2)
	{
		commander(main, sa);
		commander(main, ra);
	}
	if (sp == 1)
		commander(main, rra);
	if (sp == 3)
		commander(main, ra);
	if (sp == 4)
	{
		commander(main, sa);
		commander(main, rra);
	}
}

static void	swap_3(t_main *main)
{
	t_small	small;

	small = small_maker(main);
	if (small.a_3 > small.a_2 && small.a_3 > small.a_1)
	{
		if (small.a_2 < small.a_1)
			commander(main, sa);
	}
	if (small.a_2 > small.a_3 && small.a_2 > small.a_1)
		swap_3_1(main, 1 + (small.a_3 > small.a_1));
	if (small.a_1 > small.a_2 && small.a_1 > small.a_3)
		swap_3_1(main, 3 + (small.a_2 > small.a_3));
}

void	small_swap(t_main *main)
{
	if (main->a_size == 4)
		swap_1_4(main);
	if (main->a_size == 3)
		swap_3(main);
	if (main->a_size == 2)
	{
		if (main->a_head->num < main->a_head->pre->num)
			commander(main, sa);
	}
}
