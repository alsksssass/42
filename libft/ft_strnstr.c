/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 10:46:54 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/11 20:21:02 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	needlen;
	size_t	i;

	needlen = ft_strlen(need);
	if (needlen == 0)
		return ((char *)hay);
	if (len == 0)
		return (0);
	while (*hay && len >= needlen)
	{
		if (*hay == *need)
		{
			i = 0;
			while (i++ < needlen)
			{
				if (*(hay + i) != *(need + i))
					break ;
			}
			if (i >= needlen)
				return ((char *)hay);
		}
		hay++;
		len--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char	*s1;
	char	*s2;
	char	*s;
	size_t	max;

	s1 = "MZIRIBMZIRIBMZE123";
	s2 = "MZIRIBMZE";
	s = "AAAAAAAAAAAAA";
	max = strlen(s2);
	printf("%s\n",ft_strnstr(((void *)0), "fake", 3));
//	printf("%s\n",strnstr(((void *)0), "fake", 3));
		return (0);
}
*/
