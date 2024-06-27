/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:40:38 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/23 13:11:20 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if(!str)
		return (i);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}
/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void) {
  char str[] = "hello world";
  int len1, len2;

  // ft_strlen 함수를 사용하여 문자열의 길이를 계산합니다.
  len1 = ft_strlen(str);
  printf("len1: %d\n", len1);

  // strlen 함수를 사용하여 문자열의 길이를 계산합니다.
  len2 = strlen(str);
  printf("len2: %d\n", len2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(len1 == len2);

  // ft_strlen 함수를 사용하여 빈 문자열의 길이를 계산합니다.
  len1 = ft_strlen("");
  printf("len1: %d\n", len1);

  // strlen 함수를 사용하여 빈 문자열의 길이를 계산합니다.
  len2 = strlen("");
  printf("len2: %d\n", len2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(len1 == len2);

  return (0);
}
*/
