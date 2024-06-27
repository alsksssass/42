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
void qq_note(t_check *cmd)
{
	if (cmd->qq_mark == 1)
		cmd->qq_mark =0;
	else if (cmd->qq_mark == 0)
		cmd->qq_mark =1;
}

void q_note(t_check *cmd)
{
	if (cmd->q_mark == 1)
		cmd->q_mark =0;
	else if (cmd->q_mark == 0)
		cmd->q_mark =1;
}
void q_swap(t_check *cmd, char *mark, int i)
{
	if(mark[i] == '\'' && cmd->qq_mark ==1)
		mark[i] = 1;
	if(mark[i] == '\"' && cmd->q_mark ==1)
		mark[i] = 127;
	if(mark[i] == '$' && cmd->q_mark ==1)
		mark[i] = 2;
}
int q_mark (t_check *cmd, char *mark)
{
	int i;

	i = 0;
	while(mark[i])
	{
		if (mark[i] == '\"' && cmd->q_mark != 1)
			qq_note(cmd);
		if (mark[i] == '\'' && cmd->qq_mark !=1 )
			q_note(cmd);
		if(cmd->q_mark == 1 || cmd->qq_mark == 1)
			q_swap(cmd,mark,i);
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

int triple_strcmp(char *str, char *set)
{
	if(ft_strnstr(str,set,ft_strlen(str)))
		return 1;
	return 0;
}

int triple_char(char *str)
{
	if (triple_strcmp(str,"<<<") == 1)
		return 1;
	if (triple_strcmp(str,">>>") == 1)
		return 1;
	if (triple_strcmp(str,"||") == 1)
		return 1;
	return 0;
}

void eof_doller(char *str)
{
	char *need;
	int i;

	i = 2;
	need = 0;
	need = ft_strnstr(str,"<<",ft_strlen(str));
	if (need)
	{
		while(i < 4)
		{
			if(*(need+i) =='$')
				*(need+i) = 2;
			i++;
		}
	}
}
int error_cmd(char *str)
{
	t_check check;
	ft_bzero(&check,sizeof(t_check));
	if (ft_strcmp(str,";\\")==1)
		return 1;
	if (q_mark(&check,str) == 1)
		return 1;
	if (triple_char(str) == 1)
		return 1;
	eof_doller(str);
	return 0;
}
int cmd_check(char *input)
{
	if (error_cmd(input) == 1)
			return error_message("minishell: syntax error\n",1);
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

int check_mark(char input)
{
    char *split_mark = "|<>";
    while (*split_mark)
    {
        if (*split_mark == input)
            return (1);
        if (input == 0)
            return (0);
        split_mark++;
    }
    return (0);
}

int make_split_cmd(t_main *main, int i)
{
	int j;
    int k;
    int first;
    char m;

	j = 0;
    k = 0;
    first = 0;
    m = 0;
    while(main->input[j])
    {
        if (main->cmd[i] == NULL)
            main->cmd[i] = (char *)ft_calloc(sizeof(char), (ft_strlen(main->input) + 1));
        while ((main->input[j] == ' ' || main->input[j] == '\t') && first == 0 && m == 0)
            j++;
        if (!main->input[j])
            break;
        if (first == 0 && check_mark(main->input[j]) != 0 && m == 0)
        {
            main->cmd[i][k++] = main->input[j++];
            while (main->input[j] == main->input[j - 1])
                main->cmd[i][k++] = main->input[j++];
            i++;
            k = 0;
            continue;
        }
        first = 1;
        if (first == 1 && (check_mark(main->input[j]) != 0 || main->input[j] == ' ' || main->input[j] == '\t') && m == 0)
        {
            i++;
            k = 0;
            first = 0;
            continue;
        }
        if ((main->input[j] == '\'' || main->input[j] == '\"') && m == 0)
            m = main->input[j];
        else if (m != 0 && m == main->input[j])
            m = 0;
        main->cmd[i][k++] = main->input[j++];
    }
	printf("1%s1   len =%zu\n",main->cmd[i],ft_strlen(main->cmd[i]));
	if(ft_strlen(main->cmd[i]) == 0)
	{
		free(main->cmd[i]);
		main->cmd[i] = 0;
	}

	return (0);
}

int split_cmd(t_main *main)
{
    int i;

    i = 0;

    main->cmd = (char **)ft_calloc(sizeof(char *), (ft_strlen(main->input) + 1));
	make_split_cmd(main, i);
	if (ft_strlen(main->cmd[i]) == 0)
	{
		free(main->cmd[i]);
		main->cmd[i] = 0;
	}
    return (0);
}
/*
typedef struct s_cmd
{
    char *infile;
    char *outfile;
    char **cmd;
    char *here_doc;
    int append;
    struct s_cmd *next;
}t_cmd;
*/
int cmd_len(t_main *main)
{
	char **cmd;
	int i;

	i = 0;
	cmd = main->cmd;

	while(cmd[i])
	{
		i++;
	}
	return i;
}
char *make_temp_file(int *fd)
{
	int i;
	char *path;
	char *name;
	char *num;
	i = 0;
	path = "./.temp";

	while(1)
	{
		num = ft_itoa(i);
		name = ft_strjoin(path,num);
		*fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0666);
		if (*fd != -1)
			break;
		free(num);
		i++;
	}
	free(num);
	return name;
}

void reset_here_doc(t_cmd *cmd)
{
	unlink(cmd->here_doc);
	free(cmd->here_doc);
	cmd->here_doc_fd = 0;
	cmd->here_doc = 0;
}

char *add_nl(char *str)
{
	char *send;

	send = ft_strjoin(str,"\n");
	free(str);
	return send;
}

void find_doller(char *str)
{
	if (!str)
		return ;
	while(*str)
	{
		if (*str == 2)
			*str = '$';
		str++;
	}
}
void    make_temp(t_main *main, t_cmd *cmd, char *str)
{
    char    *msg;
    char    *temp;
    size_t  size_name;
	char *end;

	find_doller(str);
	end = ft_strtrim(str,"\'\"");
    size_name = ft_strlen(end);
    while (1)
    {
		msg = readline("> ");
        if (size_name == ft_strlen(msg))
        {
            if (ft_strncmp(end, msg, size_name) == 0)
                break ;
        }
		if (!msg)
            break ;
		if(str &&!(*str == '\'' || *str == '\"'))
		{
			temp = msg;
			msg = replace_cmd(main,msg);
			if(temp != msg)
				free(temp);
		}
		msg = add_nl(msg);
		write(cmd->here_doc_fd, msg, ft_strlen(msg));
    }
	close(cmd->here_doc_fd);
	free(end);
	exit(0);
}

void here_doc_sigint_handler(int signum)
{
	printf("\n\033[s");
	(void)signum;
	exit(2);	
}
void here_doc_sigquit_handler(int signum)
{
	printf("\n\033[s");
	(void)signum;
	exit(1);	
}

int  error_code_here_doc(t_cmd *cmd, int code)
{
	int ret;

	ret = 0;
	if (code == 512)
	{
		ft_putstr_fd("\n",1);
		reset_here_doc(cmd);
		ret = 1;
	}
	sig_init(INIT);
	return ret;
}
int recive_here_doc(t_main *main, t_cmd *cmd, int  now)
{
	pid_t child;
	int code;

	code = 0;
	if (cmd->here_doc_fd != 0)
		reset_here_doc(cmd);
    cmd->here_doc = make_temp_file(&cmd->here_doc_fd);
	sig_init(IGN);
	if(!(main->cmd[now+1]))
		return 1;
	child = fork();
	if(child == 0)
	{	
		sig_init(HERE);
		make_temp(main,cmd,main->cmd[now+1]);
		sig_init(INIT);
	}
	wait(&code);
	return error_code_here_doc(cmd,code);
}

void outfile_make(t_main *main, t_cmd *cmd, int now, int append)
{
	if(cmd->outfile)
		close(cmd->outfile_fd);
	cmd->outfile = main->cmd[now+1];
	if (append == 1)
		cmd->outfile_fd = open(cmd->outfile,O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		cmd->outfile_fd = open(cmd->outfile,O_WRONLY | O_CREAT| O_TRUNC, 0666);
	cmd->append = append;

}

int infile_make(t_main *main, t_cmd *cmd, int now)
{
	if (cmd->infile && cmd->infile_fd == -1)
		return 0;
	if(cmd->infile)
		close(cmd->infile_fd);
	cmd->infile = main->cmd[now+1];
	cmd->infile_fd = open(cmd->infile, O_RDONLY);
	if(cmd->infile_fd == -1)
	{
		ft_putstr_fd(cmd->infile,2);
		ft_putstr_fd(" : ",2);
		perror("");
		return 1;
	}
	return 0;
}
int check_here_doc (t_main *main, t_cmd *cmd , int now, int add)
{
	int num;

	num = 0;
	while(now<add)
	{
		if(ft_strcmp(main->cmd[now],"<>") == 1)
		{
			if (ft_strlen(main->cmd[now]) == 2)
			{
				if(ft_strncmp(main->cmd[now],"<<",3) == 0)
				{
					num = recive_here_doc(main,cmd,now);
					if(num == 1)
						return 1;
				}
				else if(ft_strncmp(main->cmd[now],">>",3) == 0)
					outfile_make(main,cmd,now,1);
			}
			else if (ft_strlen(main->cmd[now]) == 1)
			{
				if (*main->cmd[now] == '<')
				{
					if(infile_make(main,cmd,now) ==1)
						return 1;
				}
				else
					outfile_make(main,cmd,now,0);
			}
		}
		now++;
	}
	return 0;
}


char *to_char(char *s)
{
	char **str;
	char *temp;
	char *temp2;

	if (ft_strlen(s) == 2 && ft_strncmp("\"\"",s,3) ==0)
		return ft_strdup("");
	str = ft_split_set(s,"\"\'");
	if(!*str)
		return s;
	temp = *str;
	while(*str)
	{
		str++;
		temp2 = temp;
		temp = ft_strjoin(temp,*str);
		free(temp2);
	}
	temp2 = temp;
	while(*temp)
	{
		if(*temp == 1)
			*temp = '\'';
		if(*temp == 2)
			*temp = '$';
		if(*temp == 127)
			*temp = '\"';
		temp++;
	}
	return temp2;
}
char *re_ascii(char *s)
{
	char *str;

	str = to_char(s);
	return str;
}

void default_set_cmd(t_cmd *cmd)
{
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->here_doc_fd = -1;
}

void free_node_fail(t_cmd *cmd)
{
	if(cmd->infile)
		unlink(cmd->infile);
	if(cmd->here_doc)
		unlink(cmd->infile);
}
t_cmd *make_node(t_main *main, int now, int add)
{
	t_cmd *send;
	int i;

	i = 0;
	send = ft_calloc(sizeof(t_cmd),1);
	default_set_cmd(send);
	if (check_here_doc(main, send,now,add) == 1)
		return 0;
	while (now < add)
	{
		if (ft_strcmp(main->cmd[now],"|<>") == 0)
		{
			send->cmd[i]= re_ascii(main->cmd[now]);
			i++;
		}
		else
			now++;
		now++;
	}
	if(!(send->cmd[0]))
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n",2);
		free_node_fail(send);
		free(send);
		return 0;
	}
	return send;
}


int get_next(t_main *main, int num)
{
	int i;

	i = num;
	if (num == 0)
		i = 1;
	while(main->cmd[i])
	{
		if (ft_stcmp(*main->cmd[i],"|"))
			return i;
		i++;
	}
	return i;
}
void add_node(t_cmd **cmd, t_cmd *new)
{
	t_cmd  *list;

    if (cmd == 0)
        return ;
    if (*cmd == 0)
    {
        *cmd = new;
        return ;
    }
    list = *cmd;
    while (list->next != 0)
        list = list->next;
    list->next = new;
}


char *value_check(char *str)
{
	char *set;
	char *temp;

	set = 0;
	if(*str == '\'')
		set = "\'";
	if(*str == '\"')
		set = "\"";
	if (set == 0)
		return str;
	else
	{
		temp = str;
		set = ft_strtrim(str,set);
		free(temp);
		return set;
	}
}

int  make_cmd(t_main *main)
{
	char **cmd;
	t_cmd *node; 
	int i;
	int j;

	i = 0;
	cmd = main->cmd;
	while(cmd[i])
	{
		j = get_next(main,i);
		node = make_node(main,i,j);
		if(node == NULL)
			return 1;
		add_node(&main->cmd_list,node);
		i = j;
		if (!cmd[i])
			break;
		i++;
	}
	return 0;
}
void print_cmd(t_main *main)
{
	t_cmd *cmd;
	int i;

	i = 0;
	cmd = main->cmd_list;

	while(cmd)
	{
		printf("cmd [%i]\n",i);
		printf("chiled_pid [%d]\n",cmd->child);
		printf("infile [%s]\n",cmd->infile);
		printf("infile_fd [%d]\n",cmd->infile_fd);
		printf("outfile [%s]\n",cmd->outfile);
		printf("outfile_fd [%d]\n",cmd->outfile_fd);
		printf("//command //\n");
		for(int i =0;cmd->cmd[i]; i++)
			printf("cmd = %s\n",cmd->cmd[i]);
		printf("heredoc [%s]\n",cmd->here_doc);
		printf("heredoc_fd [%d]\n",cmd->here_doc_fd);
		printf("append [%d]\n",cmd->append);
		printf("\n\n");
		cmd = cmd->next;
		i++;
	}
}
