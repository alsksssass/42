/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:38:16 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/14 15:09:46 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	countw(char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s == c && j > 0)
		{
			i++;
			j = 0;
		}
		else if (*s != c)
			j++;
		s++;
	}
	if (j > 0)
		i++;
	return (i);
}

static void	freem(char **send, int cwd)
{
	int	i;

	i = 0;
	while (i < cwd)
	{
		free(send[i]);
		i++;
	}
	free(send);
}

static int	malcheck(char **send, char *s, int *n, int *i)
{
	*(send + (*i)) = ft_substr(s - (*n), 0, *n);
	if (!(*(send + (*i))))
	{
		freem(send, *i);
		return (0);
	}
	*n = 0;
	*i += 1;
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**send;
	int		i;
	int		j;
	int		cwd;

	cwd = countw(s, c);
	j = 0;
	i = 0;
	send = (char **)malloc(sizeof(char *) * (cwd + 1));
	if (!send)
		return (0);
	while (cwd > i)
	{
		if ((*s == c && j > 0) || (*s == 0 && j > 0))
		{
			if (!malcheck(send, s, &j, &i))
				return (0);
		}
		else if (*s != c)
			j++;
		s++;
	}
	send[i] = 0;
	return (send);
}
