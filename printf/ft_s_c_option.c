/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_c_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:52:59 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/30 16:55:12 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s1, t_str *list)
{
	char	*ptr;
	int		len;

	if (!s1)
	{
		return (ft_strdup("(null)", list));
	}
	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ft_bzero(ptr, len + 1);
	ft_strlcpy(ptr, (char *)s1, len + 1);
	list->t_len = len;
	return (ptr);
}

char	*ft_chardup(const char c, t_str *list)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * 2);
	if (!ptr)
		return (0);
	ft_bzero(ptr, 2);
	ptr[0] = c;
	list->t_len = 1;
	return (ptr);
}
