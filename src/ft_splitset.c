

#include <stdlib.h>

static int	ft_stcmp(char *s1, char *s2)
{
	unsigned char	*u1;
	unsigned char	*u2;
	unsigned int	i;

	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	i = 0;
	while (u2[i])
	{
		if (*u1 == (u2[i]))
			return (1);
		i++;
	}
	return (-1);
}

static void	put_in(char **send, char *str, int num, int *tag)
{
	int	i;

	i = 0;
	*(send + (*tag)) = (char *)malloc(sizeof(char) * (num + 1));
	i = 0;
	while (num > 0)
	{
		send[(*tag)][i] = *(str - num);
		i++;
		num--;
	}
	send[(*tag)][i] = 0;
	*tag += 1;
}

static int	check(char *str, char *charset)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (*str)
	{
		if ((ft_stcmp(str, charset) == 1 && ii != 0))
		{
			ii = 0;
			i++;
		}
		else if ((ft_stcmp(str, charset) == -1))
			ii++;
		str++;
	}
	if (ii > 0)
		i++;
	return (i);
}

char	**ft_split_set(char *str, char *charset)
{
	int		i;
	int		ii;
	char	**send;

	send = (char **)malloc(sizeof(char *) * (check(str, charset) + 1));
	if (send == 0)
		return (0);
	ii = 0;
	i = 0;
	while (*str)
	{
		if ((ft_stcmp(str, charset) == 1 && ii != 0))
		{
			put_in(send, str, ii, &i);
			ii = 0;
		}
		else if ((ft_stcmp(str, charset) == -1))
			ii++;
		str++;
	}
	if (ii > 0)
		put_in(send, str, ii, &i);
	*(send + i) = 0;
	return (send);
}
