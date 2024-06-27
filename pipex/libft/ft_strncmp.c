/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:26:55 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/07 15:49:47 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((*(us1 + i) || *(us2 + i)) && i < n)
	{
		if (*(us1 + i) != *(us2 + i))
		{
			if ((*(us1 + i) - *(us2 + i)) > 0)
				return (1);
			return (-1);
		}
		i++;
	}
	return (0);
}
/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void) {
  char str1[] = "hello world";
  char str2[] = "cat net";
  int n1, n2;

  // ft_strncmp 함수를 사용하여 문자열을 비교합니다.
  n1 = ft_strncmp(str1, str2, 5);
  printf("n1: %d\n", n1);

  // strncmp 함수를 사용하여 문자열을 비교합니다.
  n2 = strncmp(str1, str2, 5);
  printf("n2: %d\n", n2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(n1 == n2);

  // ft_strncmp 함수를 사용하여 빈 문자열을 비교합니다.
  n1 = ft_strncmp("", "", 1);
  printf("n1: %d\n", n1);

  // strncmp 함수를 사용하여 빈 문자열을 비교합니다.
  n2 = strncmp("", "", 1);
  printf("n2: %d\n", n2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(n1 == n2);

  // ft_strncmp 함수를 사용하여 같은 문자열을 비교합니다.
  n1 = ft_strncmp("asd", "asf", 5);
  printf("n1: %d\n", n1);

  // strncmp 함수를 사용하여 같은 문자열을 비교합니다.
  n2 = strncmp("asd", "asf", 5);
  printf("n2: %d\n", n2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(n1 == n2);

  return (0);
}
*/
