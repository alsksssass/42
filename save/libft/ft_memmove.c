/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:21:15 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/10 19:41:58 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char		*d1;
	const unsigned char	*s1;

	d1 = (unsigned char *)dest;
	s1 = (const unsigned char *)src;
	if (d1 == 0 && s1 == 0)
		return (0);
	if (d1 > s1)
	{
		while (num-- > 0)
			*(d1 + num) = *(s1 + num);
	}
	else
	{
		while (num > 0)
		{
			*d1 = *s1;
			num--;
			d1++;
			s1++;
		}
	}
	return (dest);
}
