/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:44:24 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/27 10:38:59 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (us1 == 0 && us2 == 0)
		return (0);
	while (n > 0)
	{
		*us1 = *us2;
		us1++;
		us2++;
		n--;
	}
	return (s1);
}
/*
 #include <stdio.h>
 #include <string.h>

 int main()
 {
	int a[]  = {1,2,3,4,5};
	int b[]  = {6,7,8,9};
	int c[]  = {1,2,3,4,5};
	int d[]  = {6,7,8,9};
	printf("%d\n",(int)ft_memcpy((void *)0,(void *)0,5));
	printf("%d\n",(int)memcpy((void *)0,(void *)0,5));
	return (0);
 }
 */
