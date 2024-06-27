/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_swap_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:47:12 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 12:47:20 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_4_3(t_main *main, int sp, int num)
{
	if (sp == 6)
	{
		commander(main, sa);
		commander(main, ra);
		if (num == 0)
			commander(main, sa);
	}
	if (sp == 7)
	{
		commander(main, ra);
		commander(main, sa);
		commander(main, rra);
		commander(main, rra);
		if (num == 1)
			commander(main, sa);
	}
	if (sp == 8)
	{
		commander(main, rra);
		commander(main, rra);
		if (num == 0)
			commander(main, sa);
	}
}

static void	swap_4_4(t_main *main, int sp, int num)
{
	if (sp == 10 && num == 1)
	{
		commander(main, pb);
		commander(main, sa);
		commander(main, ra);
		commander(main, pa);
		commander(main, ra);
	}
	if (sp == 10 && num == 0)
	{
		commander(main, pb);
		commander(main, rra);
		commander(main, pa);
		commander(main, ra);
	}
	if (sp == 11)
	{
		commander(main, sa);
		commander(main, ra);
		commander(main, ra);
		if (num == 0)
			commander(main, sa);
	}
}

void	swap_2_4(t_main *main, t_small small)
{
	if (small.a_2 > small.a_4 && small.a_2 > small.a_3 && small.a_2 > small.a_1)
	{
		if (small.a_4 > small.a_1 && small.a_4 > small.a_3)
			swap_4_3(main, 6, (small.a_3 > small.a_1));
		if (small.a_3 > small.a_1 && small.a_3 > small.a_4)
			swap_4_3(main, 7, (small.a_4 > small.a_1));
		if (small.a_1 > small.a_4 && small.a_1 > small.a_3)
			swap_4_3(main, 8, (small.a_4 > small.a_3));
	}
	if (small.a_1 > small.a_4 && small.a_1 > small.a_3 && small.a_1 > small.a_2)
	{
		if (small.a_4 > small.a_3 && small.a_4 > small.a_2)
		{
			commander(main, ra);
			if (small.a_2 > small.a_3)
				commander(main, sa);
		}
		if (small.a_3 > small.a_4 && small.a_3 > small.a_2)
			swap_4_4(main, 10, (small.a_4 > small.a_2));
		if (small.a_2 > small.a_3 && small.a_2 > small.a_4)
			swap_4_4(main, 11, (small.a_4 > small.a_3));
	}
}
