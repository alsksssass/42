/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_a_to_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:47:35 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 12:51:57 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	tiny_bot(t_main *main, int sp)
{
	if (sp == 1)
	{
		commander(main, sa);
	}
}

static void	tiny_mid(t_main *main, int sp)
{
	if (sp == 1)
	{
		commander(main, ra);
		commander(main, sa);
		commander(main, rra);
		commander(main, sa);
	}
	else
	{
		commander(main, ra);
		commander(main, sa);
		commander(main, rra);
	}
}

static void	tiny_top(t_main *main, int sp)
{
	if (sp == 1)
	{
		commander(main, sa);
		commander(main, ra);
		commander(main, sa);
		commander(main, rra);
		commander(main, sa);
	}
	else
	{
		commander(main, sa);
		commander(main, ra);
		commander(main, sa);
		commander(main, rra);
	}
}

int	tiny_swap(t_main *main, int min, int max, t_pivot pivot)
{
	int	a_top;
	int	a_mid;
	int	a_bot;

	a_top = main->a_head->pre->num;
	a_mid = main->a_head->pre->pre->num;
	a_bot = main->a_head->pre->pre->pre->num;
	if (max - min == 2)
	{
		if (main->a_head->pre->pre->num < main->a_head->pre->num)
			commander(main, sa);
	}
	else if (max - min == 3 && max - pivot.pivot_2 == 1 && pivot.pivot_2
		- pivot.pivot_1 == 1)
	{
		if (a_bot > a_top && a_bot > a_mid)
			tiny_bot(main, (a_top > a_mid));
		else if (a_mid > a_top && a_bot < a_mid)
			tiny_mid(main, (a_top > a_bot));
		else if (a_mid < a_top && a_bot < a_top)
			tiny_top(main, (a_mid > a_bot));
	}
	else
		return (0);
	return (1);
}
