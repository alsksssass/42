/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:35:32 by sabyun            #+#    #+#             */
/*   Updated: 2023/12/05 11:12:18 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int str);
int		ft_isalpha(int str);
int		ft_isascii(int str);
int		ft_isdigit(int str);
int		ft_isprint(int str);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int str);
int		ft_toupper(int str);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t num);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *hay, const char *need, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

typedef struct s_str
{
	char	*send;
	int		s_len;
	int		t_len;
}	t_str;

char	*pf_ft_substr(char const *s, unsigned int start, size_t len);
int		ft_printf(const char *s, ...);
int		get_string(const char *s, int *size, t_str *list);
char	*pf_ft_strjoin(t_str *list, char *s2, int num);
int		check_option(const char *s, t_str *list, va_list ap);
char	*print_hex(unsigned long long addr, char hex_p, t_str *list);
char	*pf_ft_strdup(const char *s1, t_str *list);
char	*ft_chardup(const char c, t_str *list);
char	*long_ft_itoa(long long n, t_str *list);
int		free_nul(int num, const char *s, ...);
char	*get_next_line(int fd);
int		checker(char **save, char *buff, char **send);
size_t	ft_strlen_2(const char *str, int c, int p);
char	*ft_strjoin_2(char const *s1, char const *s2);
void	*ft_memcpy_2(void *s1, const void *s2, size_t n);
char	*ft_substr_2(char const *s, size_t start, size_t len);
void	ft_elcheck(int size, char **save, char **send);
#endif
