/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:29:36 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/12 18:36:49 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*send;

	i = 0;
	send = (char *)malloc(ft_strlen(s) + 1);
	if (!send)
		return (0);
	while (*s)
	{
		send[i] = f(i, *s);
		s++;
		i++;
	}
	send[i] = 0;
	return (send);
}
