/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:17:44 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/23 16:38:18 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
