/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:39:13 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/06 19:43:41 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	mlen;
	char	*ptr;
	size_t	i;

	i = (size_t)start;
	mlen = ft_strlen(s);
	if (len < mlen && (ft_strlen(s) > start) && !(mlen < start + len))
		mlen = len;
	else if (ft_strlen(s) <= start)
	{
		i = mlen;
		mlen = 0;
	}
	else if (mlen < start + len)
		mlen -= start;
	else
		mlen = ft_strlen(s + start);
	ptr = (char *)malloc(mlen + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, (char *)s + i, mlen + 1);
	return (ptr);
}
