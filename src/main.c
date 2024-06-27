#include "minishell.h"

// void change_env(t_main *main, char *str)
// {
// 	int i;
// 	char *send;
// 	char *env;
// 	char *temp;
// 	i = 0;
// 	temp = str;
// 	while(*temp == '$')
// 	{
// 		temp++;
// 		i++;
// 	}
// 	send = ft_substr(str,0,i);
// 	main = 0;
// //	env = get_env(str,temp);
// 	env = 0;
// 	temp = send;
// 	send = ft_strjoin(send,temp);
// 	free(env);
// 	free(temp);
// 	temp = str;
// 	str = send;
// 	free((void *)temp);
// }

int duble_len(char **str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		i++;
	}
	return i;
}
int is_num(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return 1;
		i++;
	}
	return 0;
}
int is_alnum_str(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return 1;
		if(str[i]==2)
			return 1;
		i++;
	}
	return 0;
}
int check_num(char *num)
{
	if (is_num(num) == 1)
	{
		ft_putstr_fd("numeric argument required\n",2);
		return 255;
	}
	if (ft_strlen(num) > 19)
	{
        ft_putstr_fd("numeric argument required\n",2);
		return 255;
	}
	return 0;
}
int exit_num(char **cmd)
{
	int i;

	i = 0;
    ft_putstr_fd("exit\n",1);

	if(cmd[1])
	{
		i = check_num(cmd[1]);
		if (i == 0)
			i = ft_atoi(cmd[1]);
	}
	if (i == 0 && duble_len(cmd) >2)
	{
		print_error(cmd[0], "too many arguments");
		exit(255);
	}
	exit(i);
}

void	debug_arr(char **arr)
{
	for (int i = 0; arr[i]; i++)
		printf("[%s]\n", arr[i]);
}
int get_envplen(char **arr)
{
	int cnt;

	cnt = 0;
	while (*arr++)
		cnt++;
	return (cnt);
}
int	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (0);
}

// void add_export(char *cmd, t_main *main)
// {
// 	int i;
// 	char **tmp;

// 	i = 0;
// 	tmp = ft_calloc(sizeof(char*), get_envplen(main->envp) + 1);
// 	while(main->envp[i])
// 	{
// 		tmp[i] = ft_calloc(sizeof(char) , ft_strlen(main->envp[i]) + 1);
// 		tmp[i] = ft_memcpy(tmp[i], main->envp[i], ft_strlen(main->envp[i]) + 1);
// 		i++;
// 	}
// 	 tmp[i] = ft_calloc(sizeof(char) , ft_strlen(cmd) + 1);
// 	 tmp[i] = ft_memcpy(tmp[i], cmd, ft_strlen(cmd) + 1);
// 	 //free_split(main->envp);
// 	 //main->envp = tmp;
// }

// void del_export(char *cmd, char **envp)
// {
// 	printf("[del-export]\n");
// 	debug_arr(envp);
// 	printf("[%s]\n", cmd);
// }
 

void free_cmdlist(char **cmd)
{
	int i;

	i = 0;
	while(cmd[i])
	{
		free((void *)cmd[i]);
		i++;
	}
	free(cmd);
	cmd = 0;
}

void free_cmd(t_main *main)
{
	t_cmd *cmd;
	t_cmd *temp;
		
	free(main->input);
	free_cmdlist(main->cmd);
//	free_cmdlist(main->envp);
	temp = 0;
	main->input = 0;
	cmd = main->cmd_list;
	while(cmd)
	{	
		free(temp);
		temp = 0;
//		free(cmd->infile);
//		free(cmd->outfile);
//		free(cmd->here_doc);
//		free_cmdlist(cmd->cmd);
		if(cmd->here_doc_fd != 0)
		{	
			unlink(cmd->here_doc);
			free(cmd->here_doc);
		}
		temp = cmd;
		cmd = cmd->next;
	}
	if(cmd)
		free(cmd);
	main->cmd_list = 0;
}
char *make_str(char *str, int set)
{
	int i;

	i =0;
	if(!str || !*str)
		return 0;
	while(str[i] && str[i] != set)
			i++;
	return ft_substr(str,0,i);
}
char *ascii_env(char *s)
{
	char *str;
	char *ret;
	str = ft_strdup(s);
	ret = str;
	while(*str)
	{
		if (*str == '\"')
			*str = 127;
		if (*str == '\'')
			*str = 1;
		str++;
	}
	return ret;
}
char *daller_env()
{
	char *ret;
	char *str;

	ret = ft_strdup("$");
	str = ret;
	while(*str)
	{
		if(*str == '$')
			*str = 4;
		str++;
	}
	return ret;
}
char *get_env(t_envp *env, char *str)
{
	printf("str in env %s\n",str);
	if(!*str)
		return daller_env();
	printf("str in env %s\n",str);
	while(env)
	{
		if (ft_strncmp(env->key,str,ft_strlen(str)+1) ==0)
		{
				free((void *)str);
				if (!env->value)
					return 0;
				return ascii_env(env->value);
		}
		env = env->next;
	}
	return 0;
}


char *after_make_str(t_main *main, char *str)
{
	char *env;
	char *send;
	char *temp;
	char *temp2;
	int i;
	i = 0;

	printf("str  == %s1\n",str);
	while(str[i] !='$' && str[i])
			i++;
	env =&str[i];
	i = 1;
	if (*env == '$')
	{
		while(env[i] && (ft_isalnum(env[i]) == 1 ||env[i] == '_'))
				i++;
	}
	if((env + i) - (str+ft_strlen(str)) >0)
		return str;
	temp = ft_substr(str,0,env-str);
	temp2 = make_str(env+i,0);
	if (temp2 && ft_strncmp(temp2,"?",1) == 0)
	{
		env = ft_substr(temp2,1,ft_strlen(temp2+1));
		free(temp2);
		temp2 = ft_itoa(exit_code);
		send = ft_strjoin(temp2,env);
		free(temp2);
		temp2 = send;
		send =0;
		free(env);
		env = 0;
	}
	else
		env = get_env(main->envp_list,ft_substr(env,1,i-1));
	send = ft_strjoin(temp,env);
	free(temp);
	free(env);
	env = send;
	send = ft_strjoin(env,temp2);
	free(env);
	free(temp2);
	printf("send  == %s1\n",send);
	return send;

}

char *ret_daller_env(char *str)
{
	char *ret;

	ret = str;
	while(*str)
	{
		if(*str == 4)
			*str = '$';
		str++;
	}
	return ret;
}
char *replace_cmd(t_main *main, char *cmd)
{
	char *mark;
	char *send;
	char *temp;

	temp = 0;
	send = 0;
	mark = ft_strchr(cmd,'\"');
	if (mark)
		send = after_make_str(main,cmd);
	else
	{
		mark = ft_strchr(cmd,'$');
		if (mark)
			send = after_make_str(main,cmd);
		else
			send = cmd;
	}
	mark = send;
	send = ft_strjoin(temp,send);
	free(mark);
	if (ft_strchr(send,'$'))
	{
		temp = send;
		send = replace_cmd(main,send);
		free(temp);
	}
	return ret_daller_env(send);
}

void sigint_handler (int signum)
{
	signum = 0;
	rl_replace_line("", 1);
	rl_on_new_line();
	printf("\n\033[s");
	rl_redisplay();
	exit_code = 1;
}

void sigquit_handler(int signum) {
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
	printf("\n\033[s");
}

void save_cursor(void)
{
	printf("\033[s");
}
void a(void)
{
	system("leaks minishell");
}

void syntax(int *syn, char *str)
{
	if(*str == '<' || *str == '>')
		*syn = RED;
	else if(*str == '|')
		*syn = PIP;
	else if(*str == '$')
		*syn = DAL;
	else
		*syn = ARG;
}
int error_check_syn(int syn, int pre)
{
	if (pre == FIR || syn == FIR)
		return 0;
	if(pre == RED && (syn ==RED))
		return 1;
	if(pre == PIP && (syn == PIP))
		return 1;
	return 0;
}
int check_syntax(char **cmd)
{
	int pre;
	int syn;
	
	syn = FIR;
	pre = FIR;
	while(*cmd)
	{
		syntax(&syn,*cmd);
		if(error_check_syn(syn,pre) == 1)
		{
			ft_putstr_fd("syntax error near unexpected token '",2);
			ft_putstr_fd(*cmd,2);
			ft_putstr_fd("'\n",2);
			return 1;
		}
		pre = syn;
		cmd++;
	}
	if (pre == PIP || pre == RED)
	{
		ft_putstr_fd("syntax error",2);
		ft_putstr_fd("\n",2);
		return 1;
	}
	return 0;
}
int main(int argc, char **argv, char **envp) 
{
	t_main main;
	(void)argc;
	(void)argv;
//	atexit(a);
	ft_bzero(&main,sizeof(t_main));
	main.envp = envp;
	main.fd_tmp = -1;
	main.std[0] = dup(STDIN_FILENO);
	main.std[1] = dup(STDOUT_FILENO);
  	exit_code = main.exit_state;
	defult_envp(&main);
	//rl_event_hook = &save_cursor;
	sig_init(INIT);
	while(1)
	{

		main.input = readline("minishell: ");
		if (!main.input)
		{
			printf("\033[u\033[13C\033[1B\033[1Aexit\n");
			break;
		}
		if (*main.input == 0)
			continue;
		add_history(main.input);
		if (cmd_check(main.input) == 1)
		{
			exit_code = 258;
			free(main.input);
			continue ;
		}
		main.input = replace_cmd(&main,main.input);
		if (split_cmd(&main) != 0)
		{
			exit_code = 258;
			free_cmd(&main);
			continue ;
		}
		for(int i = 0; main.cmd[i];i++)
			printf("cmd[%d] = %s\n",i,main.cmd[i]);
		if(check_syntax(main.cmd) ==1)
		{
			exit_code = 258;
			free_cmd(&main);
			continue ;
		}
		if (make_cmd(&main) == 1)
		{
			exit_code = 1;
			free_cmd(&main);
			continue ;
		}
		//env_process(&main);
		print_cmd(&main);
		//printf("print\n");
		do_cmd(&main);// cmd_list 차례로 실행시키는 부분
		sig_init(INIT);
		free_cmd(&main);
	}
//	rl_clear_history();
	close(main.std[0]);
	close(main.std[1]);
	return 0;
}
