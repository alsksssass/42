/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_set_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:45:24 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 10:49:21 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static int	malloc_index(t_main *main)
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

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
		i++;
	}
	if (i > 10)
		return (0);
	return (1);
}

static int	check_num(char *str)
{
	if (!is_num(str))
		return (error_message());
	if (*str == '-' && ft_strlen(str + 1) == 10)
	{
		if (ft_strncmp(str + 1, "2147483648", 10) > 0)
			return (error_message());
	}
	else if (*str == '+' && ft_strlen(str + 1) == 10)
	{
		if (ft_strncmp(str + 1, "2147483647", 10) > 0)
			return (error_message());
	}
	else if (ft_strlen(str) == 10 && ft_strncmp(str, "2147483647", 10) > 0)
		return (error_message());
	return (1);
}

int	default_set(t_main *main, int argc, char **argv)
{
	if (argc == 1)
		return (0);
	main->list = argv_sort(argv, argc);
	main->save = main->list;
	while (*main->list)
	{
		if (!*main->list)
			return (error_message());
		if (!check_num(*main->list))
			return (0);
		stack_maker(main, *main->list++);
	}
	if (!malloc_index(main))
		return (error_message());
	if (!sorted(main) || main->total == 1)
		return (0);
	return (1);
}
