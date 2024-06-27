/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:27:34 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/27 11:49:06 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	len(int n)
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

static char	*numchar(int size, int n, int umm)
{
	char	*send;

	send = (char *)malloc(sizeof(char) * (size + 1 + umm));
	if (!send)
		return (0);
	if (umm == 1)
	{
		send [size + umm] = 0;
		size++;
	}
	else
		send [size] = 0;
	send[0] = 0 + '0';
	while (n > 0)
	{
		size--;
		send[size] = n % 10 + '0';
		n /= 10;
	}
	if (umm == 1)
		send [size - 1] = '-';
	return (send);
}

char	*ft_itoa(int n)
{
	int	i;
	int	umm;

	umm = 0;
	if (n < 0)
	{
		n *= -1;
		umm = 1;
	}
	i = len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (numchar(i, n, umm));
}
/*
#include <stdio.h>

int main ()
{
	printf("%s",ft_itoa(-2147483648));
	return 0;
}
*/
