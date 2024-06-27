/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:59:03 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 11:59:05 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	find_index(int num, int *arr, int size)
{
	while (--size > 0)
	{
		if (arr[size] == num)
			break ;
	}
	return (size);
}

static int	indexing(t_main *main)
{
	int		*index;
	int		i;
	t_stack	*a;

	i = 0;
	if (!main->a_head)
		return (0);
	a = main->a_head->pre;
	index = main->sort;
	while (i < main->a_size)
	{
		a->num = find_index(a->num, index, main->a_size);
		a = a->pre;
		i++;
	}
	return (1);
}

int	malloc_index(t_main *main)
{
	int	*temp;
	int	i;

	i = 0;
	while (main->b_head)
		p_ab(main, pa);
	(main->list) -= (main->size);
	temp = (int *)malloc(sizeof(int) * main->total);
	while (i < main->size)
	{
		temp[i] = ft_atoi(main->list[i]);
		i++;
	}
	main->sort = temp;
	quick_sort(main->sort, 0, main->size - 1);
	if (!indexing(main))
		return (0);
	return (1);
}
