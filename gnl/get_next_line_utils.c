/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:23:02 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/29 12:30:58 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
