/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:20:58 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/12 18:24:14 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long long	ln;
	char		num;

	ln = n;
	if (ln < 0)
	{
		ln *= -1;
		write(fd, "-", 1);
	}
	if (ln >= 10)
		ft_putnbr_fd(ln / 10, fd);
	num = (ln % 10) + '0';
	write(fd, &num, 1);
}
/*
int main()
{
	ft_putnbr_fd(0,2);
	return 0;
}
*/
