/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:58:44 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 11:58:47 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static t_stack	*make_new(t_main *main, char *num)
{
	t_stack	*send;

	send = (t_stack *)malloc(sizeof(t_stack));
	if (!send)
		return (0);
	send->num = ft_atoi(num);
	send->next = 0;
	send->pre = 0;
	main->size += 1;
	main->total += 1;
	return (send);
}

void	stack_in(t_stack **stack, t_stack *new, int *size)
{
	t_stack	*base;

	*size += 1;
	base = *stack;
	if (!*stack)
	{
		*stack = new;
		new->next = new;
		new->pre = new;
	}
	else
	{
		new->pre = base->pre;
		base->pre->next = new;
		new->next = *stack;
		(*stack)->pre = new;
	}
}

void	stack_maker(t_main *main, char *argv)
{
	t_stack	*new;

	new = make_new(main, argv);
	stack_in(&main->b_head, new, &main->b_size);
}

t_stack	*stack_pop(t_stack **stack, int *size)
{
	t_stack	*send;

	if (*size == 1)
	{
		send = *stack;
		*stack = 0;
	}
	else
	{
		send = (*stack)->pre;
		(*stack)->pre->pre->next = *stack;
		(*stack)->pre = (*stack)->pre->pre;
	}
	*size -= 1;
	return (send);
}
