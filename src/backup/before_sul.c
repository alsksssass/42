/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:58:22 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/08 11:36:31 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_stcmp(char s1, char *s2)
{
    unsigned char   u1;
    unsigned char   *u2;
    unsigned int    i;

    u1 = (unsigned char)s1;
    u2 = (unsigned char *)s2;
    i = 0;
    while (u2[i])
    {
        if (u1 == (u2[i]))
            return (1);
        i++;
    }
    return (-1);
}


int ft_strcmp(char *s1, char *s2)
{
	while(*s1)
	{
		if(ft_stcmp(*s1,s2) == 1)
			return 1;
		s1++;
	}
	return 0;
}

int counter(char *str,char *charset)
{
        t_count count;

        ft_bzero(&count,sizeof(t_count));
    while(str[count.i])
    {
        if (ft_stcmp(str[count.i],charset) == 1)
        {
                if (count.k !=0)
                {
                    count.k = 0;
                    count.set++;
                }
                count.j++;
        }
        else if (ft_stcmp(str[count.i],charset) == -1)
        {
                if (count.j !=0)
                {
                    count.j = 0;
                    count.cmd++;
                }
                count.k++;
        }
        count.i++;
    }
    return (count.set+count.cmd);
}

char    *ft_substr1(char const *s, unsigned int start, size_t len)
{
    size_t  mlen;
    char    *ptr;
    size_t  i;

    i = (size_t)start;
    mlen = ft_strlen(s);
    if (len < mlen && (ft_strlen(s) > start) && !(mlen < start + len))
        mlen = len;
    else if (ft_strlen(s) <= start)
    {
        i = mlen;
        mlen = 0;
    }
    else if (mlen < start + len)
        mlen -= start;
    else
        mlen = ft_strlen(s + start);
    ptr = (char *)malloc(mlen + 1);
    if (!ptr)
        return (0);
    ft_strlcpy(ptr, (char *)s + i, mlen + 1);
    return (ptr);
}

void get_split(char *str, t_count *count)
{
	char **send;
	int num;
	int k;
	
	char aa;
	if (count->k !=0)
		k = count->k;
	else
		k = count->j;
	num = (count->i) - k;
	aa= *(str+num);
	send = count->str;
	if (num <= 0)
		num = 0;
	if (*(str+num) == ' ')
		send[(count->set)] = ft_strdup("");
	else
		send[(count->set)] = ft_substr(str,num,k);
	count->k = 0;
	count->j = 0;
	count->set++;
}
void q_mark_sub(t_count *count,char *start, int i)
{
	count->str[count->set] = ft_substr(start,0,i);
	count->i += (i - (count->k));
	count->set ++;
	count->k = 0;
}
void meet_qmark(t_count *count, char *str)
{
	char *start;
	int i;
	int meet;
	char test;
	meet = 0;
	i = 0;
	start = str + (count->i - count->k);

	while (start[i])
	{
		test = start[i];
		if(ft_stcmp(start[i],"\'\"") == 1)
		{
			if(meet ==2)
				meet =0;
			meet += 1;
		}
		if(meet == 2 && ft_stcmp(start[i]," <>|$") == 1)
		{
			q_mark_sub(count,start,i);
			return;
		}
		i++;

	}
	q_mark_sub(count,start,i);
}

void char_set_pc(t_count *count ,char *str)
{
	if (ft_stcmp(str[count->i - count->k],"\"\'") == 1)
	{
			meet_qmark(count,str);
			if(ft_stcmp(str[count->i]," \'\"<>|$"))
				count->j++;
			return ;
	}
	if (count->j !=0 && (*(str+(count->i - count->j)) != *(str + count->i) ||ft_stcmp(str[count->i - count->k],"\"\'")))
	{
		if (*(str+ (count->i - count->j)) == ' ')
			count->str[count->set] = ft_strdup("");
		else
			count->str[count->set] =ft_substr(str+(count->i - count->j),0,count->j);
		count->j = 0;
		count->set++;
	}
	else if (count->k !=0)
		get_split(str,count);
	count->j++;
}

void str_set_pc(t_count *count ,char *str)
{

	if (ft_stcmp(str[count->i - count->j],"\"\'") == 1)
	{
		meet_qmark(count,str);
		if(ft_stcmp(str[count->i]," \'\"<>|$"))
			count->j++;
		return ;
	}
	if (count->j !=0)
		get_split(str,count);
	count->k++;
}
void spliter(char **send, char *str,char *charset)
{
	t_count count;

	ft_bzero(&count,sizeof(t_count));
	count.str = send;
	while(str[count.i])
	{
		if (ft_stcmp(str[count.i],charset) == 1)
				char_set_pc(&count,str);
		else if (ft_stcmp(str[count.i],charset) == -1)
			str_set_pc(&count,str);
		count.i++;
	}
	get_split(str,&count);
	count.str[count.set] = 0;
}

char **cmd_split(char *str , char *charset)
{
    t_split split;
	int i;

	i = 0;
    ft_bzero(&split,sizeof(t_split));
	int res = counter(str,charset);
    split.send = malloc(sizeof(char *) * (res + 10 +1));
	spliter(split.send,str,charset);
    return (split.send);
}

void here_doc (t_check *cmd, char mark)
{
	if (mark == '<')
		{
			if (cmd->here_doc_mark == 0)
				cmd->here_doc_mark =1;
			else if (cmd->here_doc_mark == 1)
				cmd->here_doc_mark =2;
			else if (cmd->here_doc_mark == 2)
			{
				cmd->here_doc_mark =-1;
				cmd->error = 1;
			}
		}
		if (mark == '>')
		{
			if (cmd->re_direction_mark == 0)
				cmd->re_direction_mark =1;
			else if (cmd->re_direction_mark == 1)
				cmd->re_direction_mark =2;
			else if (cmd->re_direction_mark == 2)
			{
				cmd->re_direction_mark =-1;
				cmd->error = 1;
			}
		}
	return ;
}

int q_mark (t_check *cmd, char *mark)
{
	int i;

	i = 0;
	while(mark[i])
	{
	if (mark[i] == '\"' && cmd->q_mark != 1)
		{
			if (cmd->qq_mark == 1)
				cmd->qq_mark =0;
			else if (cmd->qq_mark == 0)
				cmd->qq_mark =1;
		}
		if (mark[i] == '\'' && cmd->qq_mark !=1 )
		{
			if (cmd->q_mark == 1)
				cmd->q_mark =0;
			else if (cmd->q_mark == 0)
				cmd->q_mark =1;
		}
		i++;
	}
		if(cmd->qq_mark == 1 || cmd->q_mark ==1)
			return 1;
	return 0;
}

int error_message(char *str, int error_num)
{
	ft_putstr_fd(str,2);

	return error_num;
}
int error_cmd(char *str)
{
	t_check check;
	ft_bzero(&check,sizeof(t_check));
	if (ft_strcmp(str,";\\")==1)
		return 1;
	if (q_mark(&check,str) == 1)
		return 1;
	return 0;
}
int cmd_check(char *input)
{
	int i;
	i = 0;
	if (error_cmd(input) == 1)
		return error_message("error_command\n",1);
	/*
	while (input[i])
	{
		if (input[i] =='<'|| input[i] =='>')
			check.here_doc +=1;
		if (input[i] =='\"' || input[i] =='\'' )
			q_mark(&check,input[i]);
		if (input[i] =='$')
			check.export +=1;
		i++;
	}
	*/
	return 0;
}
void base (t_main *main, char *str)
{
	char *a;

	a = str;
	main->char_set = " <|>$";
	
}



int main() 
{
	t_main main;
	int len;

	ft_bzero(&main,sizeof(t_main));

		char *input = readline("Minishell: ");

		base(&main,input);
		char **pipe;

		if (cmd_check(input) == 1)
		{
			printf("cmd error\n");
			return 1;
		}
		pipe = cmd_split(input,main.char_set);
		int i = 0;
		len =0 ;
		while(pipe[i])
		{
			len += ft_strlen(pipe[i]);
			printf("num [%d] = [%s]  len = %d\n",i,pipe[i],len);
			i++;
		}


	return 0;
}

		
