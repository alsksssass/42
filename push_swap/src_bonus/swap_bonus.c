/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:58:16 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 11:58:18 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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
		if (main->a_size < 2)
			return ;
		send1 = stack_pop(&main->a_head, &main->a_size);
		send2 = stack_pop(&main->a_head, &main->a_size);
		stack_in(&main->a_head, send1, &main->a_size);
		stack_in(&main->a_head, send2, &main->a_size);
	}
	if (command == sb || command == ss)
	{
		if (main->b_size < 2)
			return ;
		send1 = stack_pop(&main->b_head, &main->b_size);
		send2 = stack_pop(&main->b_head, &main->b_size);
		stack_in(&main->b_head, send1, &main->b_size);
		stack_in(&main->b_head, send2, &main->b_size);
	}
}

void	r_ab(t_main *main, int command)
{
	if (command == ra || command == rr)
	{
		if (!main->a_head)
			return ;
		main->a_head = main->a_head->pre;
	}
	if (command == rb || command == rr)
	{
		if (!main->b_head)
			return ;
		main->b_head = main->b_head->pre;
	}
}

void	rr_ab(t_main *main, int command)
{
	if (command == rra || command == rrr)
	{
		if (!main->a_head)
			return ;
		main->a_head = main->a_head->next;
	}
	if (command == rrb || command == rrr)
	{
		if (!main->b_head)
			return ;
		main->b_head = main->b_head->next;
	}
}

void	commander(t_main *main, int command)
{
	if (command == pa || command == pb)
		p_ab(main, command);
	if (command == sa || command == sb || command == ss)
		s_ab(main, command);
	if (command == ra || command == rb || command == rr)
		r_ab(main, command);
	if (command == rra || command == rrb || command == rrr)
		rr_ab(main, command);
}
