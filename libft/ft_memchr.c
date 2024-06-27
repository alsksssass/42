/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:59:43 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/07 19:19:18 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	sc;

	sc = (unsigned char)c;
	str = (unsigned char *)s;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*str == sc)
			return ((void *)(str));
		str++;
		n--;
	}
	return (0);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void) {
  char str[] = "hello world";
  char *ptr1, *ptr2;
	char *src = "/|\x12\xff\x09\x42\042\42|\\";
	int size = 2;
  // ft_memchr 함수를 사용하여 문자열에서 'o' 문자를 찾습니다.
  ptr1 = ft_memchr(src, '\x42', 2);
printf("%s\n",ptr1);
  // memchr 함수를 사용하여 문자열에서 'o' 문자를 찾습니다.
  ptr2 = memchr(src, '\x42', 2);
printf("%s\n",ptr2);
  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(ptr1 == ptr2);

  // ft_memchr 함수를 사용하여 문자열에서 'z' 문자를 찾습니다.
  ptr1 = ft_memchr(str, 'z', strlen(str));

  // memchr 함수를 사용하여 문자열에서 'z' 문자를 찾습니다.
  ptr2 = memchr(str, 'z', strlen(str));

  // 두 함수의 결과값이 동일한지 확인합니다.
  assert(ptr1 == ptr2);

  return (0);
}
*/
