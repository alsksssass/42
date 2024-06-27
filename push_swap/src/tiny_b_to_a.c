/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:52:07 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 12:54:53 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	tiny_bot(t_main *main, int sp)
{
	if (sp == 1)
	{
		commander(main, pa);
		commander(main, sb);
		commander(main, pa);
		commander(main, sa);
		commander(main, pa);
	}
	else
	{
		commander(main, rb);
		commander(main, sb);
		commander(main, pa);
		commander(main, pa);
		commander(main, rrb);
		commander(main, pa);
	}
}

static void	tiny_mid(t_main *main, int sp)
{
	if (sp == 1)
	{
		commander(main, sb);
		commander(main, pa);
		commander(main, pa);
		commander(main, pa);
	}
	else
	{
		commander(main, sb);
		commander(main, pa);
		commander(main, sb);
		commander(main, pa);
		commander(main, pa);
	}
}

static void	tiny_top(t_main *main, int sp)
{
	if (sp == 1)
	{
		commander(main, pa);
		commander(main, pa);
		commander(main, pa);
	}
	else
	{
		commander(main, pa);
		commander(main, sb);
		commander(main, pa);
		commander(main, pa);
	}
}

void	less_then_2(t_main *main, int max, int min)
{
	if (max - min <= 2)
	{
		if (max - min == 2)
		{
			if (main->b_head->pre->num > main->b_head->pre->pre->num)
			{
				commander(main, pa);
				commander(main, pa);
			}
			else if (main->b_head->pre->num < main->b_head->pre->pre->num)
			{
				commander(main, sb);
				commander(main, pa);
				commander(main, pa);
			}
		}
		if (max - min == 1)
			commander(main, pa);
		return ;
	}
}

int	tiny_swap_to_a(t_main *main, int min, int max, t_pivot pivot)
{
	int	b_top;
	int	b_mid;
	int	b_bot;

	b_top = main->b_head->pre->num;
	b_mid = main->b_head->pre->pre->num;
	b_bot = main->b_head->pre->pre->pre->num;
	if (max - min <= 2)
		less_then_2(main, max, min);
	else if (max - min == 3 && max - pivot.pivot_2 == 1 && pivot.pivot_2
		- pivot.pivot_1 == 1)
	{
		if (b_bot > b_top && b_bot > b_mid)
			tiny_bot(main, (b_top > b_mid));
		else if (b_mid > b_top && b_bot < b_mid)
			tiny_mid(main, (b_top > b_bot));
		else if (b_mid < b_top && b_bot < b_top)
			tiny_top(main, (b_mid > b_bot));
	}
	else
		return (0);
	return (1);
}
