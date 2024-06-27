/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: somilee <somilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:26:55 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/01 01:38:29 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (0);
	while ((*(us1 + i) || *(us2 + i)) && i < n)
	{
		if (*(us1 + i) != *(us2 + i))
		{
			if ((*(us1 + i) - *(us2 + i)) > 0)
				return (1);
			return (-1);
		}
		i++;
	}
	return (0);
}
