/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:00:13 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/14 14:56:50 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	c1;

	s1 = (unsigned char *)s;
	c1 = (unsigned char)c;
	while (n > 0)
	{
		*s1 = c1;
		s1++;
		n--;
	}
	return (s);
}
/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void) {
  char str1[] = "hello world";
  char str2[] = "hello world";
  int n = strlen(str1);
	printf("%s\n",str1);
	printf("%s\n",str2);


  //ft_memset 함수를 사용하여 문자열을 0으로 초기화합니다.
  ft_memset(str1, 'h', 1);

  //memset 함수를 사용하여 문자열을 0으로 초기화합니다.
  memset(str2, 'h', 1);

  // 두 문자열이 동일한지 확인합니다.
   assert(strcmp(str1, str2) == 0);
	printf("%s\n",str1);
	printf("%s\n",str2);

  //ft_memset 함수를 사용하여 문자열을 'a'로 초기화합니다.
  ft_memset(str1, 'a', n);

  // memset 함수를 사용하여 문자열을 'a'로 초기화합니다.
  memset(str2, 'a', n);

  // 두 문자열이 동일한지 확인합니다.
  assert(strcmp(str1, str2) == 0);
	printf("%s\n",str1);
	printf("%s\n",str2);

  return (0);
}
*/
