/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:23:24 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/29 12:32:09 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		checker(char **save, char *buff, char **send);
size_t	ft_strlen_2(const char *str, int c, int p);
char	*ft_strjoin_2(char const *s1, char const *s2);
void	*ft_memcpy_2(void *s1, const void *s2, size_t n);
char	*ft_substr_2(char const *s, size_t start, size_t len);
void	ft_elcheck(int size, char **save, char **send);

#endif
