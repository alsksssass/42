/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:38:54 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/07 19:14:07 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c1;

	c1 = (char)c;
	while (*s)
	{
		if (*s == c1)
			return ((char *)s);
		s++;
	}
	if (c1 == '\0')
		return ((char *)s);
	return (0);
}
/*
#include <string.h>

int main (int argc, char **argv)
{
	if(argc == 0)
		return (0);
	printf("%p\n",ft_strchr("teste", '\0'));
	//printf("%p\n",strchr("teste", '\0'));
	return (0);
}
*/
