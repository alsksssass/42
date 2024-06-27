/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:19:57 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/15 15:13:24 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;

	srclen = (size_t)ft_strlen(src);
	destlen = (size_t)ft_strlen(dest);
	if (size <= destlen)
		return (srclen + size);
	ft_strlcpy(dest + destlen, (char *)src, size - destlen);
	return (srclen + destlen);
}
