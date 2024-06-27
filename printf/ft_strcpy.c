/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:17:51 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/30 17:16:39 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (us1 == 0 && us2 == 0)
		return (0);
	while (n > 0)
	{
		*us1 = *us2;
		us1++;
		us2++;
		n--;
	}
	return (s1);
}

char	*ft_strjoin(t_str *list, char *s2, int num)
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

int	num_len(unsigned long long num)
{
	int	i;

	i = 1;
	while (num > 15)
	{
		num /= 16;
		i++;
	}
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

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
