/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:44:14 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/14 14:49:42 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*temp;

	if (!del || !lst)
		return ;
	list = *lst;
	temp = 0;
	while (list != 0)
	{
		temp = list;
		list = temp->next;
		if (temp->content)
			del(temp->content);
		free(temp);
	}
	*lst = 0;
}
