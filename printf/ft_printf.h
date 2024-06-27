/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:50:06 by sabyun            #+#    #+#             */
/*   Updated: 2023/11/04 12:35:00 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_str
{
	char	*send;
	int		s_len;
	int		t_len;
}	t_str;

size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_printf(const char *s, ...);
int		get_string(const char *s, int *size, t_str *list);
char	*ft_strjoin(t_str *list, char *s2, int num);
int		check_option(const char *s, t_str *list, va_list ap);
char	*print_hex(unsigned long long addr, char hex_p, t_str *list);
int		num_len(unsigned long long num);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s1, t_str *list);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
char	*ft_chardup(const char c, t_str *list);
char	*ft_itoa(long long n, t_str *list);
int		free_nul(int num, const char *s, ...);

#endif
