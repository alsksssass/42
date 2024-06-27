/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:23:02 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/27 10:36:02 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_2(void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (us1 == 0 && us2 == 0)
		return (0);
	while (n-- > 0)
	{
		*us1 = *us2;
		us1++;
		us2++;
	}
	*us1 = 0;
	return (s1);
}

char	*ft_substr_2(char const *s, size_t start, size_t len)
{
	size_t	mlen;
	char	*ptr;
	size_t	i;

	if (!*s)
		return (0);
	i = (size_t)start;
	mlen = ft_strlen_2(s, 0, 0);
	if (len < mlen && (ft_strlen_2(s, 0, 0) > start) && !(mlen < start + len))
		mlen = len;
	else if (ft_strlen_2(s, 0, 0) <= start)
	{
		i = mlen;
		mlen = 0;
	}
	else if (mlen < start + len)
		mlen -= start;
	else
		mlen = ft_strlen_2(s + start, 0, 0);
	ptr = (char *)malloc(mlen + 1);
	if (!ptr)
		return (0);
	ft_memcpy_2(ptr, (char *)s + i, mlen);
	return (ptr);
}

void	ft_elcheck(int readsize, char **save, char **send)
{
	if (*save)
		*send = ft_substr_2(*save, 0, ft_strlen_2(*save, '\n', 0));
	if (readsize < 0)
	{
		free(*send);
		*send = 0;
	}
	free(*save);
	*save = 0;
	return ;
}
