/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:53:45 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/10 19:22:35 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*dest;
	char	c1;

	c1 = (char)c;
	dest = 0;
	while (*s)
	{
		if (*s == c1)
			dest = (char *)s;
		s++;
	}
	if (c1 == '\0')
		return ((char *)s);
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*src;

	src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
	printf("%s\n",strrchr(src,'\0'));
	printf("%s\n",ft_strrchr(src,'\0'));
	return (0);
}
*/
