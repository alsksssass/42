/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_set_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:56:36 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 10:45:40 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_index(int num, int *arr, int size)
{
	while (--size > 0)
	{
		if (arr[size] == num)
			break ;
	}
	return (size);
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
					return (error_message());
				j++;
			}
			i++;
		}
	}
	return (1);
}

char	**argv_sort(char **argv, int argc)
{
	char	**send;
	char	*save;
	char	*temp;
	int		i;

	i = 1;
	save = 0;
	while (i < argc)
	{
		temp = save;
		save = ft_strjoin(save, argv[i]);
		if (temp)
			free(temp);
		temp = save;
		save = ft_strjoin(save, " ");
		if (temp)
			free(temp);
		i++;
	}
	send = ft_split(save, ' ');
	free(save);
	return (send);
}

int	sorted(t_main *main)
{
	int		*arr;
	char	**lists;
	int		i;

	i = 0;
	arr = main->sort;
	lists = main->list;
	if (!equal_num(arr, main->total))
		return (0);
	while (i + 1 < main->total)
	{
		if (ft_atoi(lists[i]) > ft_atoi(lists[i + 1]))
			return (1);
		i++;
	}
	return (0);
}
