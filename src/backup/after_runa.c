/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:58:22 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/13 11:09:55 by sabyun           ###   ########.fr       */
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
    return (0);
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

char *get_sp(t_split *split)
{
	char *send;

	if (ft_strncmp(split->str,"<<",2) || ft_strncmp(split->str,">>",2))
	{
		send = ft_substr(split->str,0,2);
		(split->str)+=2;
	}
	else
	{
		send = ft_substr(split->str,0,1);
		(split->str)+=1;
	}
	return send;
}

int move_to_end(t_split *split, t_count *count)
{
	int check;

	check = 0;
	while(*split->str)
	{
		if (ft_stcmp(*split->str,"\'\"") ==1)
		{
			if (check ==0)
				check = *split->str;
			else if(check == *split->str)
				check = 0;
		}
		else if (ft_stcmp(*split->str," <>|$") ==1)
			return 0;
		split->str++;
		(count->i)++;
	}
	return 1;
}
char *get_word(t_split *split)
{
	t_count count;

	ft_bzero(&count,sizeof(t_count));
	while(*split->str)
	{
		if (ft_stcmp(*split->str,"\"\'") == 1)
		{
			if (move_to_end(split,&count) == 1)
				break;
		}
		if (ft_stcmp(*split->str," <>|$") == 1)
			return (ft_substr(split->str,0,count.i));
		split->str++;
	}
	return (ft_substr(split->str,0,count.i));
}
char *spliter(t_split *split)
{
	t_count count;

	ft_bzero(&count,sizeof(t_count));
	if (!split->str)
		return 0;
	if (ft_stcmp(*split->str,split->char_set) == 1)
		return(get_sp(split));
	else
		return(get_word(split));
}

char **cmd_split(char *str)
{
    t_split split;
	int i;

	i = 0;
    ft_bzero(&split,sizeof(t_split));
    split.send = malloc(sizeof(char *) * (ft_strlen(str)+1));
	split.str = str;
	split.char_set = " \"\'<>$|";

	while(1)
	{
		split.send[i] = spliter(&split);
		if (split.send[i] == 0)
			break;
		i++;
	}
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

void str_int(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		printf(" no.%d = %c\n",i,str[i]);
		i++;
	}
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
		str_int(input);
		pipe = cmd_split(input);
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

		
