/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:20:11 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/07 17:56:38 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv)
{
	char	*s;
	char	*a;

	s = "abc";
	a = "abc";
	if(argc == 0)
		return (0);
	printf("%d\n",ft_memcmp(*(argv+1), *(argv +2), 7));
	printf("%d\n",memcmp(*(argv+1), *(argv+2), 7));
	return (0);
}
*/
