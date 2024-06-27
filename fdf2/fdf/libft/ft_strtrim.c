/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:47:45 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/14 15:08:34 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trimcmp(char str, char const *c)
{
	while (*c)
	{
		if (str == (char)*c)
			return (1);
		c++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ahead;
	char	*tail;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	len = ft_strlen(s1);
	ahead = (char *)s1;
	tail = (char *)s1 + len - 1;
	if (len == 0)
		return ((char *)ft_calloc(1, 1));
	while (trimcmp(*(ahead + i), set) == 1)
		i++;
	while (trimcmp(*(tail - j), set) == 1 && j < len)
		j++;
	if (len > i + j)
		return (ft_substr(s1, i, len - j - i));
	return ((char *)ft_calloc(1, 1));
}
