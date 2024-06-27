#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
typedef struct s_list 
{
	char *send ;
	char buff [BUFFER_SIZE + 1];
	int fd;
	int error;
	int read_size;
	struct s_list *next;
}	t_list;

void    ft_bzero(void *s, size_t n);
t_list  *ft_lstlast(t_list *lst, int fd);
char *get_next_line(int fd);
#endif
