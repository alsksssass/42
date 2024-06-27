/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:58:54 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 11:58:57 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	swap(int *arr, int i, int j)
{
	int	temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

static int	q_parting(int *arr, int min, int max)
{
	int	i;
	int	j;
	int	pivot;

	pivot = arr[max];
	i = min;
	j = min;
	while (i <= max)
	{
		if (arr[i] <= pivot)
			swap(arr, i, j++);
		i++;
	}
	return (j - 1);
}

void	quick_sort(int *arr, int min, int max)
{
	int	pivot;

	if (min < max)
	{
		pivot = q_parting(arr, min, max);
		quick_sort(arr, min, pivot - 1);
		quick_sort(arr, pivot + 1, max);
	}
	else
		return ;
}
