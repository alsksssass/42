/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:47:59 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/27 19:51:02 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_point
{
	int x;
	int y;
	int z;
	double a;
	double b;
	int color;
} t_point;

typedef struct s_vars
{
	void *mlx;
	void *win;
}	t_vars;

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int **point;
	int **color;
	int y;
	int x;
	int deg_a;
	int deg_b;
	int term;
	int x_c;
	int y_c;
	int high;
}   t_data;

#endif
