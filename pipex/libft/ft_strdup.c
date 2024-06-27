/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:15:36 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/10 22:00:38 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = malloc(ft_strlen(s1) + 1);
	if (ptr == 0)
		return (0);
	ft_strlcpy(ptr, (char *)s1, ft_strlen(s1) + 1);
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
	printf("%s\n",ft_strdup("lorem ipsum dolor sit amet"));
	printf("%s\n",strdup("lorem ipsum dolor sit amet"));
}
*/
