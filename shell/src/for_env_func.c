/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:14:33 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/04 10:14:35 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*q_replace(char *s)
{
	char	*str;
	char	*head;
	char	*tail;
	char	*send;

	str = ft_strnstr(s, "\"\"", ft_strlen(s));
	if (str)
	{
		head = ft_substr(s, 0, str - s);
		tail = ft_substr(str + 2, 0, ft_strlen(str + 2));
		str = daller_env(17);
		send = ft_strjoin(head, str);
		free(head);
		send = ft_strjoin(send, tail);
		free(tail);
		free(s);
		return (send);
	}
	return (s);
}

char	*to_char_nomal(char *s)
{
	char	*temp;
	char	*temp2;

	temp = re_moveq(s);
	temp2 = temp;
	while (temp && *temp)
	{
		if (*temp == 1)
			*temp = '\'';
		if (*temp == 3)
			*temp = '$';
		if (*temp == 127)
			*temp = '\"';
		if (*temp == 6)
			*temp = '|';
		temp++;
	}
	return (temp2);
}
