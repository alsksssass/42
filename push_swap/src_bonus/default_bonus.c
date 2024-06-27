/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:59:24 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 14:02:11 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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

static int	equal_num(int *arr, int max)
{
	int	i;
	int	j;

	i = 0;
	if (max > 1)
	{
		while (i < max)
		{
			j = i + 1;
			while (j < max)
			{
				if (arr[i] == arr[j])
					return (0);
				j++;
			}
			i++;
		}
	}
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
	if (!malloc_index(main) || !equal_num(main->sort, main->total))
		return (error_message());
	return (1);
}
