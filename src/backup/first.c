/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:58:22 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/07 11:11:45 by sabyun           ###   ########.fr       */
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

	if (count->k !=0)
		k = count->k;
	else
		k = count->j;
	num = (count->i) - k;
	send = count->str;
	if (num <= 0)
		num = 0;
	send[(count->set)] = ft_substr1(str,num,k);
	count->k = 0;
	count->j = 0;
	count->set++;
}
void spliter(char **send, char *str,char *charset)
{
	t_count count;

	ft_bzero(&count,sizeof(t_count));
	count.str = send;
	while(str[count.i])
	{
		if (ft_stcmp(str[count.i],charset) == 1)
		{
			if (count.k !=0)
				get_split(str,&count);
			count.j++;
		}
		else if (ft_stcmp(str[count.i],charset) == -1)
		{
			if (count.j !=0)
				get_split(str,&count);
			count.k++;
		}
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
    split.send = malloc(sizeof(char *) * (counter(str,charset) +1));
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
	if (mark[i] == '"' && cmd->q_mark != 1)
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
/*
void join_qmark(t_main *main, char **cmd, int num)
{
	int q_mark;
	int i;
	
	q_mark = cmd[num][0];

	if (cmd[num][1] !=0 && cmd[num][1] == q_mark)
		

	i = 0;
	q_mark = 0;
	while(cmd[i])
	{
		cmd[i];
		i++;
	}
}

int alternater(char **cmd,t_main *main)
{
	int i;
	int q_mark;

	q_mark = 0;
	i = 0;
	while(cmd[i])
	{
		if(ft_stcmp(cmd[i],"\"\'") == 1)
		{
		//	join_qmark(main,cmd[i],&i);
		}
		make_cmd(cmd[i],main);
		i++;
	}
	if(q_mark == 1)
		return 1;
	return 0;
}
*/
void base (t_main *main, char *str)
{
	char *a;

	a = str;
	main->char_set = "\"<|>\'$";
	
}

char *get_set(char str)
{
	if (str == '\"')
		return "<|>$\'";
	else
		return "<|>$\"";
}
int meet_qmark(char *str)
{
	int i;
	char tmp;
	int count;
	char *set;

	count = 0;
	i = 0;
	set = get_set(str[i]);
	tmp = str[i];
	while(str[i])
	{
		if (str[1] != 0 && tmp == str[1])
			return -1;
		if(ft_stcmp(str[i],"\"\'") == 1 && i !=0 && count !=1)
		{
			if (tmp == str[i])
				count = 1;
		}
		else if(count == 1 && (str[i] == ' ' || ft_stcmp(str[i],set) == 1))
			break;
		i++;
	}
	return i;
}
int get_token(char *str,int *len,t_main *main)
{
	char tmp;
	int i;

	i = 0;
	if(ft_stcmp(*str,main->char_set) == 1)
	{
		if (*str == '\'' || *str == '\"')
			i = meet_qmark(str);
		else
		{
			tmp = *str;
			if (*(str + 1) != 0 && *(str + 1) == tmp)
				i= 2;
			else
				i=1;
		}
	}
	if (i != -1)
		*len += i;
	return i;
}
char *token(char *str,t_main *main, int *num)
{
	int i;
	int len;
	char *send;
	char *temp;

	temp = 0;
	len = 0;
	send = 0;
	i = 0;
	if (!str)
		return 0;
	while(str[i])
	{
		if(ft_stcmp(str[i],main->char_set) == 1)
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				if(get_token(str+len,&len,main) == -1)
				{
					//if (len !=0)
					//	break;
					temp = ft_substr(str,0,len);
					len = 0;
					i+=2;
					continue;
					//return token(str+2,main,num);
					//case     a''b "" abc "asb"
				}
			}
			else if(len ==0)
				get_token(&str[i],&len,main);
			send = ft_substr(str,0,len);
			break;
		}
		else if (str[i] ==' ')
		{
			send = ft_substr(str,0,len++);
			break;
		}
		len++;
		i++;
	}
	if (!send && len !=0 && temp == 0)
		send = ft_substr(str,0,len);
	if(temp)
	{
		send = ft_substr(str+(i-len),0,len);
		send = ft_strjoin(temp,send);
		len += i;
	}
	*num += len;
	return send;
}


int main() 
{
	t_main main;

	ft_bzero(&main,sizeof(t_main));

		char *input = readline("Minishell: ");

		base(&main,input);
//		char *pipe;

		if (cmd_check(input) == 1)
		{
			printf("cmd error\n");
			return 1;
		}
		int i = 0;
		while(input[i])
		{
			printf("%s\n",token(&input[i],&main,&i));
		}


	return 0;
}

		
