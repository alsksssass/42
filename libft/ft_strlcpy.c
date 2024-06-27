/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:18:48 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/13 16:07:48 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (*src)
	{
		if (i + 1 < size)
		{
			*dest = *src;
		}
		else
		{
			break ;
		}
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	return (src_len);
}
/*

#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void) {
  char src[] = "hello world";
  char dest1[6], dest2[6];
  int n = 5;

  // ft_strlcpy 함수를 사용하여 문자열을 복사합니다.
  ft_strlcpy(dest1, src, n);
  printf("dest1: %s\n", dest1);

  // strlcpy 함수를 사용하여 문자열을 복사합니다.
  strlcpy(dest2, src, n);
  printf("dest2: %s\n", dest2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(strcmp(dest1, dest2) == 0);

  // ft_strlcpy 함수를 사용하여 문자열을 복사합니다.
  ft_strlcpy(dest1, src, sizeof(dest1));
  printf("dest1: %s\n", dest1);

  // strlcpy 함수를 사용하여 문자열을 복사합니다.
  strlcpy(dest2, src, sizeof(dest2));
  printf("dest2: %s\n", dest2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(strcmp(dest1, dest2) == 0);

  // ft_strlcpy 함수를 사용하여 빈 문자열을 복사합니다.
  ft_strlcpy(dest1, "", sizeof(dest1));
  printf("dest1: %s\n", dest1);

  // strlcpy 함수를 사용하여 빈 문자열을 복사합니다.
  strlcpy(dest2, "", sizeof(dest2));
  printf("dest2: %s\n", dest2);

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(strcmp(dest1, dest2) == 0);

  return (0);
}

*/
