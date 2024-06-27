/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:19:30 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/23 17:09:17 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_string(const char *s, int *size, t_str *list)
{
	char	*temp;

	temp = 0;
	if (*size == 0)
		return (1);
	temp = ft_substr(s - *size, 0, *size);
	if (!temp)
		return (free_nul(0, "s", list->send));
	list->send = pf_ft_strjoin(list, temp, *size);
	*size = 0;
	if (!list->send)
		return (free_nul(0, "ss", list->send, temp));
	return (1);
}

int	check_option(const char *s, t_str *list, va_list ap)
{
	char	*temp;

	if (*s == 'c')
		temp = ft_chardup(va_arg(ap, int), list);
	else if (*s == 's')
		temp = pf_ft_strdup(va_arg(ap, char *), list);
	else if (*s == 'p')
		temp = print_hex(va_arg(ap, unsigned long long), *s, list);
	else if (*s == 'd' || *s == 'i')
		temp = long_ft_itoa(va_arg(ap, int), list);
	else if (*s == 'u')
		temp = long_ft_itoa(va_arg(ap, unsigned int), list);
	else if (*s == 'x' || *s == 'X')
		temp = print_hex(va_arg(ap, unsigned int), *s, list);
	else if (*s == '%')
		temp = ft_chardup('%', list);
	else
		temp = 0;
	if (!temp)
		return (free_nul(0, "ss", list->send, temp));
	list->send = pf_ft_strjoin(list, temp, list->t_len);
	if (!list->send)
		return (free_nul(0, "ss", temp, list->send));
	return (1);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	t_str	list;

	i = 0;
	va_start(ap, s);
	ft_bzero(&list, sizeof(list));
	while (*s)
	{
		if (*s == '%')
		{
			if (!get_string(s++, &i, &list))
				return (-1);
			if (!check_option(s++, &list, ap))
				return (-1);
		}
		else if (*s++)
			i++;
	}
	if (!get_string(s, &i, &list))
		return (-1);
	va_end(ap);
	i = write(1, list.send, list.s_len);
	return (free_nul(i, "s", list.send));
}
