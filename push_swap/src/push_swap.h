/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:02:18 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/03 14:15:37 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
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
	rrr,
}					t_command;

typedef struct s_small
{
	int				a_1;
	int				a_2;
	int				a_3;
	int				a_4;
}					t_small;
typedef struct s_pivot
{
	int				pivot_2;
	int				pivot_1;
	int				pivot;
	int				min;
	int				max;
}					t_pivot;
typedef struct s_num
{
	int				at;
	int				ab;
	int				bt;
	int				bb;
	int				pivot;
}					t_num;
typedef struct s_main
{
	struct s_stack	*a_head;
	struct s_stack	*b_head;
	char			**list;
	char			**save;
	int				size;
	int				*sort;
	int				total;
	int				recod_command;
	int				a_size;
	int				b_size;
	int				command;
}					t_main;

typedef struct s_stack
{
	int				num;
	int				index;
	struct s_stack	*next;
	struct s_stack	*pre;
}					t_stack;

int					tiny_swap_to_a(t_main *main, int min, int max,
						t_pivot pivot);
int					tiny_swap(t_main *main, int min, int max, t_pivot pivot);
void				commander(t_main *main, int command);
void				swap_1_4(t_main *main);
void				swap_2_4(t_main *main, t_small small);
t_small				small_maker(t_main *main);
void				stack_maker(t_main *main, char *argv);
int					default_set(t_main *main, int argc, char **argv);
int					find_index(int num, int *arr, int size);
int					sorted(t_main *main);
void				quick_sort(int *arr, int min, int max);
void				push_a_to_b(t_main *main, int min, int max);
void				push_b_to_a(t_main *main, int min, int max);
void				rrr_roller(t_main *main, int ra_count, int rb_count);
t_pivot				pivot_set(int min, int max);
void				commander(t_main *main, int command);
int					error_message(void);
t_stack				*stack_pop(t_stack **stack, int *size);
void				stack_maker(t_main *main, char *argv);
void				small_swap(t_main *main);
int					free_malloc(t_main *main, int num);
void				p_ab(t_main *main, int command);
void				s_ab(t_main *main, int command);
void				r_ab(t_main *main, int command);
void				rr_ab(t_main *main, int command);
void				stack_in(t_stack **stack, t_stack *new, int *size);
char				**argv_sort(char **argv, int argc);
#endif
