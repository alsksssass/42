/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:22:49 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/27 10:25:20 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checker(char **save, char *buff, char **send)
{
	char	*temp;
	size_t	i;

	temp = ft_strjoin(*save, buff);
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
