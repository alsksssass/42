/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:46:36 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 12:46:58 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_small	small_maker(t_main *main)
{
	t_small	small;

	ft_bzero(&small, sizeof(small));
	small.a_1 = main->a_head->pre->num;
	small.a_2 = main->a_head->pre->pre->num;
	small.a_3 = main->a_head->pre->pre->pre->num;
	small.a_4 = main->a_head->pre->pre->pre->pre->num;
	return (small);
}

static void	swap_4_1(t_main *main, int sp, int num)
{
	if (sp == 0 && num == 0)
		commander(main, sa);
	if (sp == 1 && num == 0)
	{
		commander(main, rra);
		commander(main, rra);
		commander(main, sa);
		commander(main, ra);
	}
	if (sp == 1 && num == 1)
	{
		commander(main, pb);
		commander(main, sa);
		commander(main, pa);
	}
	if (sp == 2)
	{
		commander(main, rra);
		commander(main, sa);
		commander(main, ra);
		commander(main, ra);
		if (num == 0)
			commander(main, sa);
	}
}

static void	swap_4_2(t_main *main, int sp, int num)
{
	if (sp == 3)
	{
		if (num == 0)
			commander(main, sa);
		commander(main, rra);
		commander(main, rra);
		commander(main, sa);
		commander(main, ra);
		commander(main, ra);
	}
	if (sp == 4)
	{
		commander(main, rra);
		if (num == 1)
			commander(main, sa);
	}
	if (sp == 5)
	{
		commander(main, sa);
		commander(main, rra);
		if (num == 0)
			commander(main, sa);
	}
}

void	swap_1_4(t_main *main)
{
	t_small	small;

	small = small_maker(main);
	if (small.a_4 > small.a_3 && small.a_4 > small.a_2 && small.a_4 > small.a_1)
	{
		if (small.a_3 > small.a_2 && small.a_3 > small.a_1)
			swap_4_1(main, 0, (small.a_2 > small.a_1));
		if (small.a_2 > small.a_3 && small.a_2 > small.a_1)
			swap_4_1(main, 1, (small.a_3 > small.a_1));
		if (small.a_1 > small.a_3 && small.a_1 > small.a_2)
			swap_4_1(main, 2, (small.a_3 > small.a_2));
	}
	else if (small.a_3 > small.a_4 && small.a_3 > small.a_2
		&& small.a_3 > small.a_1)
	{
		if (small.a_4 > small.a_1 && small.a_4 > small.a_2)
			swap_4_2(main, 3, (small.a_2 > small.a_1));
		if (small.a_2 > small.a_4 && small.a_2 > small.a_1)
			swap_4_2(main, 4, (small.a_4 > small.a_1));
		if (small.a_1 > small.a_4 && small.a_1 > small.a_2)
			swap_4_2(main, 5, (small.a_2 > small.a_4));
	}
	else
		swap_2_4(main, small);
}
