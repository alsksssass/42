/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:18:48 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/21 19:18:36 by somilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (*src)
	{
		if (i + 1 < size)
		{
			*dest = *src;
		}
		else
		{
			break ;
		}
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	return (src_len);
}
