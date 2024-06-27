/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:20:11 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 17:10:18 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	error_message(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}

static void	print_command(int command)
{
	if (command == pa)
		ft_printf("%s\n", "pa");
	if (command == pb)
		ft_printf("%s\n", "pb");
	if (command == sa)
		ft_printf("%s\n", "sa");
	if (command == sb)
		ft_printf("%s\n", "sb");
	if (command == ss)
		ft_printf("%s\n", "ss");
	if (command == ra)
		ft_printf("%s\n", "ra");
	if (command == rb)
		ft_printf("%s\n", "rb");
	if (command == rr)
		ft_printf("%s\n", "rr");
	if (command == rra)
		ft_printf("%s\n", "rra");
	if (command == rrb)
		ft_printf("%s\n", "rrb");
	if (command == rrr)
		ft_printf("%s\n", "rrr");
}

void	commander(t_main *main, int command)
{
	if (main->recod_command == 0 && (command == rb || command == ra))
		main->recod_command = command;
	else if (main->recod_command == rb || main->recod_command == ra)
	{
		if ((main->recod_command == rb && command == ra)
			|| (main->recod_command == ra && command == rb))
			print_command(rr);
		else
		{
			print_command(main->recod_command);
			print_command(command);
		}
		main->recod_command = 0;
	}
	else
		print_command(command);
	if (command == pa || command == pb)
		p_ab(main, command);
	if (command == sa || command == sb || command == ss)
		s_ab(main, command);
	if (command == ra || command == rb || command == rr)
		r_ab(main, command);
	if (command == rra || command == rrb || command == rrr)
		rr_ab(main, command);
	main->command++;
}

int	main(int argc, char **argv)
{
	t_main	main;

	ft_bzero(&main, sizeof(main));
	if (!default_set(&main, argc, argv))
		return (free_malloc(&main, 1));
	if (main.a_size < 5)
		small_swap(&main);
	else
		push_a_to_b(&main, 0, main.a_size);
	if (main.recod_command != 0)
		print_command(main.recod_command);
	return (free_malloc(&main, 0));
}
