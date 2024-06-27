/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 10:46:54 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/15 15:13:57 by sabyun           ###   ########.fr       */
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
