/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:22:49 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/29 12:38:07 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checker(char **save, char *buff, char **send)
{
	char	*temp;
	size_t	i;

	temp = ft_strjoin_2(*save, buff);
	free(*save);
	if (!temp)
	{
		*save = 0;
		return (0);
	}
	*save = temp;
	if (ft_strlen_2(*save, '\n', 1) == 0)
		return (-1);
	*send = ft_substr_2(*save, 0, ft_strlen_2(*save, '\n', 0));
	if (!*send)
		return (-1);
	i = ft_strlen_2(*save, 0, 0) - ft_strlen_2(*save, '\n', 0);
	if (i != 0)
		*save = ft_substr_2(*save, ft_strlen_2(*save, '\n', 0), i);
	if (i == 0)
		*save = 0;
	free(temp);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*send;
	char		buff[BUFFER_SIZE + 1];
	int			readsize;

	send = 0;
	while (1)
	{
		readsize = read(fd, buff, BUFFER_SIZE);
		if (readsize > 0 || (ft_strlen_2(save, '\n', 1) && readsize >= 0))
		{
			buff[readsize] = 0;
			if (checker(&save, buff, &send) == 0)
				return (send);
		}
		else
		{
			ft_elcheck(readsize, &save, &send);
			return (send);
		}
	}
}

size_t	ft_strlen_2(const char *str, int c, int p)
{
	size_t	i;
	char	c1;

	c1 = (char)c;
	i = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (c != 0 && *str == c1)
		{
			i++;
			break ;
		}
		i++;
		str++;
	}
	if (*str == c1 && p == 1)
		return (1);
	else if (*str != c1 && p == 1)
		return (0);
	return (i);
}

char	*ft_strjoin_2(char const *s1, char const *s2)
{
	size_t	total;
	char	*ptr;

	total = 0;
	total += ft_strlen_2(s1, 0, 0);
	total += ft_strlen_2(s2, 0, 0);
	ptr = (char *)malloc(total + 1);
	if (!ptr)
		return (0);
	*ptr = 0;
	ft_memcpy_2(ptr, s1, ft_strlen_2(s1, 0, 0));
	ft_memcpy_2(ptr + ft_strlen_2(s1, 0, 0), s2, ft_strlen_2(s2, 0, 0));
	return (ptr);
}

void	*ft_memcpy_2(void *s1, const void *s2, size_t n)
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
