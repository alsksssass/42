/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:49:18 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/24 14:26:55 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	char	*ptr;

	total = 0;
	total += ft_strlen(s1);
	total += ft_strlen(s2);
	ptr = (char *)malloc(total + 1);
	if (!ptr)
		return (0);
	*ptr = 0;
	ft_memcpy(ptr, s1, ft_strlen(s1));
	ft_memcpy(ptr + ft_strlen(s1), s2, ft_strlen(s2));
	*(ptr + total) = 0;
	return (ptr);
}
