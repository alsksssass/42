/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:56:46 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/14 12:01:18 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*send;

	send = (t_list *)malloc(sizeof(t_list));
	if (!send)
		return (0);
	send->content = content;
	send->next = NULL;
	return (send);
}
/*
#include <stdio.h>

int main ()
{
	t_list *aa;

	aa = ft_lstnew("hello");

	printf("%s",aa->content);
}
*/
