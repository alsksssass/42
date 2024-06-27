/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:51:41 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/30 16:58:35 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	add_hex(char **send)
{
	char	*hex_zero;

	hex_zero = "0x";
	ft_memcpy(*send, hex_zero, 2);
	return ;
}

char	*print_hex(unsigned long long addr, char hex_p, t_str *list)
{
	char	*hex;
	char	*send;
	int		len;

	if (hex_p == 'x' || hex_p == 'p')
		hex = "0123456789abcdef";
	else if (hex_p == 'X')
		hex = "0123456789ABCDEF";
	len = num_len(addr);
	if (hex_p == 'p')
		len += 2;
	send = (char *)ft_calloc((len + 1), 1);
	if (!send)
		return (0);
	list->t_len = len;
	while (len-- > 0)
	{
		send[len] = hex[addr % 16];
		addr /= 16;
	}
	if (hex_p == 'p')
		add_hex(&send);
	return (send);
}
