/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:56:18 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 11:54:54 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H
# include "libft.h"

typedef enum e_command
{
	sa,
	sb,
	ss,
	ra,
	rb,
	rr,
	pa,
	pb,
	rra,
	rrb,
	rrr
}					t_command;

typedef struct s_main
{
	struct s_stack	*a_head;
	struct s_stack	*b_head;
	char			**list;
	char			**save;
	int				size;
	int				*sort;
	int				total;
	int				a_size;
	int				b_size;

}					t_main;

typedef struct s_stack
{
	int				num;
	int				index;
	struct s_stack	*next;
	struct s_stack	*pre;
}					t_stack;

void				stack_in(t_stack **stack, t_stack *new, int *size);
void				stack_maker(t_main *main, char *argv);
t_stack				*stack_pop(t_stack **stack, int *size);
void				p_ab(t_main *main, int command);
void				s_ab(t_main *main, int command);
void				r_ab(t_main *main, int command);
void				rr_ab(t_main *main, int command);
void				commander(t_main *main, int command);
void				quick_sort(int *arr, int min, int max);
int					malloc_index(t_main *main);
int					default_set(t_main *main, int argc, char **argv);
int					transfer_2(char *command, int size);
int					error_message(void);
char				**argv_sort(char **argv, int argc);
#endif
