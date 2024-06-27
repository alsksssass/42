#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list fd_lst;
	t_list *lst_run;
	
	lst_run = ft_lstlast(&fd_lst,fd);
	while (1)
	{
		lst_run->read_size=read(fd,lst_run->buff,BUFFER_SIZE);
		if (lst_run->read == -1)
			return (0);
		ft_strjoin(lst_run->send,lst_run->buff);	
		printf("%s",lst_run->buff);
	{
return 0;	
}

t_list  *ft_lstlast(t_list *lst, int fd)
{

    t_list *new;
	while (lst)
    {
        if(lst->fd ==fd)
			return (lst);
		if (lst->next == 0)
            break ;
        lst = lst->next;
    }
	new = malloc(sizeof(t_list));
	if (!new)
		return 0;
	ft_bzero (new,sizeof(t_list));
    return (new);
}
void    ft_bzero(void *s, size_t n)
{
    unsigned char   *s1;

    s1 = (unsigned char *)s;
    while (n-- > 0)
        *s1++ = 0;
}
char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  total;
    char    *ptr;

    total = 0;
    total += ft_strlen(s1);
    total += ft_strlen(s2);
    ptr = (char *)malloc(total + 1);
    if (!ptr)
        return (0);
    *ptr = 0;
    ft_memcpy(ptr, s1, ft_strlen(s1));
    ft_memcpy(ptr + ft_strlen(s1), s2, ft_strlen(s2));
    *(ptr + total) = 0;
    return (ptr);
}

size_t  ft_strlen(const char *str)
{
    size_t  i;

    i = 0;
    while (*str)
    {
        i++;
        str++;
    }
    return (i);
}
