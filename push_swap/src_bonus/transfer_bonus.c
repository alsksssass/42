/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:58:05 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 11:58:08 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

char	**argv_sort(char **argv, int argc)
{
	char	**send;
	char	*save;
	char	*temp;
	int		i;

	i = 1;
	save = 0;
	while (i < argc)
	{
		temp = save;
		save = ft_strjoin(save, argv[i]);
		if (temp)
			free(temp);
		temp = save;
		save = ft_strjoin(save, " ");
		if (temp)
			free(temp);
		i++;
	}
	send = ft_split(save, ' ');
	free(save);
	return (send);
}

static int	transfer_3(char *command, int size)
{
	int	send;

	send = -1;
	if (ft_strncmp(command, "rra", size) == 0)
		send = (rra);
	if (ft_strncmp(command, "rrb", size) == 0)
		send = (rrb);
	if (ft_strncmp(command, "rrr", size) == 0)
		send = (rrr);
	return (send);
}

static int	transfer_2_2(char *command, int size)
{
	int	send;

	send = -1;
	if (ft_strncmp(command, "pa", size) == 0)
		send = (pa);
	if (ft_strncmp(command, "pb", size) == 0)
		send = (pb);
	if (ft_strncmp(command, "sa", size) == 0)
		send = (sa);
	if (ft_strncmp(command, "sb", size) == 0)
		send = (sb);
	if (ft_strncmp(command, "ss", size) == 0)
		send = (ss);
	if (ft_strncmp(command, "ra", size) == 0)
		send = (ra);
	if (ft_strncmp(command, "rr", size) == 0)
		send = (rr);
	if (ft_strncmp(command, "rb", size) == 0)
		send = (rb);
	return (send);
}

int	transfer_2(char *command, int size)
{
	int	send;

	send = -1;
	if (size == 2)
		send = transfer_2_2(command, size);
	else if (size == 3)
		send = (transfer_3(command, size));
	free(command);
	if (send == -1)
		error_message();
	return (send);
}
