/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:59:32 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/13 16:37:57 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	num;
	int	umm;

	num = 0;
	umm = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			umm *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * umm);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("%d\n",ft_atoi("     		-234123498ads"));
	printf("%d\n",atoi("     		-234123498ads"));
	printf("\n");
	printf("%d\n",ft_atoi("     		+2341238ads"));
	printf("%d\n",atoi("     		+2341238ads"));
	printf("\n");
	printf("%d\n",ft_atoi("     		+2 341234ads"));
	printf("%d\n",atoi("     		+2 341234ads"));
	printf("\n");
	printf("%d\n",ft_atoi("     		-234a1234ads"));
	printf("%d\n",atoi("     		-234a1234ads"));
	printf("\n");
	printf("%d\n",ft_atoi("     		-2341234ads"));
	printf("%d\n",atoi("     		-2341234ads"));
	printf("\n");
	printf("%d\n",ft_atoi("2147483649"));
	printf("%d\n",atoi("2147483649"));
	printf("\n");
	printf("%d\n",ft_atoi("     		21474836489"));
	printf("%d\n",atoi("     		21474836489"));
	printf("\n");
	printf("%d\n",ft_atoi(" \n\n-123aaa"));
	printf("%d\n",atoi(" \n\n-123aaa"));
	return (0);
}
*/
