/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:10:06 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/02 19:13:25 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	p_ab(t_main *main, int command)
{
	t_stack	*send;

	if (command == pb)
	{
		if (!main->a_head)
			return ;
		send = stack_pop(&main->a_head, &main->a_size);
		stack_in(&main->b_head, send, &main->b_size);
	}
	if (command == pa)
	{
		if (!main->b_head)
			return ;
		send = stack_pop(&main->b_head, &main->b_size);
		stack_in(&main->a_head, send, &main->a_size);
	}
}

void	s_ab(t_main *main, int command)
{
	t_stack	*send1;
	t_stack	*send2;

	if (command == sa || command == ss)
	{
		send1 = stack_pop(&main->a_head, &main->a_size);
		send2 = stack_pop(&main->a_head, &main->a_size);
		stack_in(&main->a_head, send1, &main->a_size);
		stack_in(&main->a_head, send2, &main->a_size);
	}
	if (command == sb || command == ss)
	{
		send1 = stack_pop(&main->b_head, &main->b_size);
		send2 = stack_pop(&main->b_head, &main->b_size);
		stack_in(&main->b_head, send1, &main->b_size);
		stack_in(&main->b_head, send2, &main->b_size);
	}
}

void	r_ab(t_main *main, int command)
{
	if (command == ra || command == rr)
		main->a_head = main->a_head->pre;
	if (command == rb || command == rr)
		main->b_head = main->b_head->pre;
}

void	rr_ab(t_main *main, int command)
{
	if (command == rra || command == rrr)
		main->a_head = main->a_head->next;
	if (command == rrb || command == rrr)
		main->b_head = main->b_head->next;
}
