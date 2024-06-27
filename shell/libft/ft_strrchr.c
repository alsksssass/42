/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:53:45 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/15 15:14:03 by sabyun           ###   ########.fr       */
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
