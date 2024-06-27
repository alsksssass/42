/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:59:12 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 14:00:34 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	error_message(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}

static void	free_save(t_main *main)
{
	int	i;

	i = 0;
	while (main->save[i])
		free(main->save[i++]);
	free(main->save);
}

static int	free_malloc(t_main *main, int num)
{
	t_stack	*save;

	while (main->b_head)
		p_ab(main, pa);
	save = main->a_head;
	if (save)
	{
		while (main->a_head)
		{
			p_ab(main, pb);
			if (!(main->b_head))
				break ;
			free(main->b_head);
			main->b_head = 0;
		}
	}
	if (main->sort)
		free(main->sort);
	if (main->save)
		free_save(main);
	return (num);
}

static int	check_sort_stack(t_main *main)
{
	t_stack	*a;

	if (!main->a_head || main->b_head)
		return (0);
	a = main->a_head->pre;
	while (1)
	{
		if (a == main->a_head)
			break ;
		if (a->num > a->pre->num)
			return (0);
		a = a->pre;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_main	main;
	char	*command;
	int		num_command;

	ft_bzero(&main, sizeof(main));
	if (!default_set(&main, argc, argv))
		return (free_malloc(&main, 1));
	while (1)
	{
		command = get_next_line(0);
		if (!command)
			break ;
		num_command = transfer_2(command, ft_strlen(command) - 1);
		if (num_command == -1)
			return (free_malloc(&main, 1));
		commander(&main, num_command);
	}
	if (check_sort_stack(&main) == 0)
	{
		ft_putstr_fd("KO\n", 2);
		return (free_malloc(&main, 1));
	}
	ft_putstr_fd("OK\n", 1);
	return (free_malloc(&main, 0));
}
