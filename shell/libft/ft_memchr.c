/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:59:43 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/15 15:12:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	sc;

	sc = (unsigned char)c;
	str = (unsigned char *)s;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*str == sc)
			return ((void *)(str));
		str++;
		n--;
	}
	return (0);
}
