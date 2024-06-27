/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:49:28 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/13 16:48:32 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int str)
{
	if (ft_isalpha(str))
		return (1);
	if (ft_isdigit(str))
		return (1);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf(isalnum('1') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('z') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('Z') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('A') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('a') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('$') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('0') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('!') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum(' ') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('~') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('	') ? "알파넘버\n" : "알파넘버아님\n");
	printf(isalnum('\0') ? "알파넘버\n" : "알파넘버아님\n");
}
*/
