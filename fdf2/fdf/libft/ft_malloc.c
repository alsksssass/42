/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:17:44 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/23 17:10:05 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_nul(int num, const char *s, ...)
{
	va_list	ap;
	char	*addr;

	va_start(ap, s);
	while (*s)
	{
		if (*s == 's')
		{
			addr = va_arg(ap, char *);
			free(addr);
			addr = 0;
		}
		s++;
	}
	va_end(ap);
	return (num);
}

char	*pf_ft_strjoin(t_str *list, char *s2, int num)
{
	char	*ptr;
	size_t	s1len;
	size_t	s2len;

	s1len = list->s_len;
	s2len = num;
	ptr = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ptr)
	{
		free_nul(1, "s", list->send);
		return (0);
	}
	ft_memcpy(ptr, list->send, s1len);
	ft_memcpy(ptr + s1len, s2, s2len);
	list->s_len += num;
	free_nul(1, "ss", list->send, s2);
	return (ptr);
}

