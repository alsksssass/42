/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:55:35 by sabyun            #+#    #+#             */
/*   Updated: 2023/10/14 14:52:33 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	trans_lst(t_list *lst, t_list **first, void *(*f)(void *))
{
	t_list	*list;
	t_list	*new;
	void	*content;

	list = lst;
	while (list != 0)
	{
		content = f(list->content);
		if (!content)
			return (0);
		new = ft_lstnew(content);
		if (!new)
		{
			free(content);
			return (0);
		}
		ft_lstadd_back(first, new);
		list = list->next;
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;

	head = 0;
	if (!del || !f)
		return (0);
	if (!(trans_lst(lst, &head, f)))
	{
		ft_lstclear(&head, del);
		return (0);
	}
	return (head);
}
