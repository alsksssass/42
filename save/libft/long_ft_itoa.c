/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:27:34 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/15 15:14:19 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	len(long long n)
{
	int	i;

	if (n == 0)
		i = 1;
	else
		i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*numchar(long long size, long long n, long long umm)
{
	char	*send;

	send = (char *)malloc(sizeof(char) * (size + 1 + umm));
	if (!send)
		return (0);
	send[size] = 0;
	send[0] = 0 + '0';
	while (n > 0)
	{
		size--;
		send[size] = n % 10 + '0';
		n /= 10;
	}
	if (umm == 1)
		send[--size] = '-';
	return (send);
}

char	*long_ft_itoa(long long n, t_str *list)
{
	long long	i;
	long long	umm;

	i = 0;
	umm = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
		umm = 1;
	}
	i += len(n);
	list->t_len = i;
	return (numchar(i, n, umm));
}
