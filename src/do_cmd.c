
#include "minishell.h"

int envplist_num(t_envp *lst)
{
	int cnt;

	cnt = 0;
	while (lst)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}
int cmdlist_num(t_cmd *lst)
{
	int cnt;

	cnt = 0;
	while (lst)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}

void	print_error(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

char **make_envp_arr(t_envp *lst)
{
	char **envp;
	char *tmp;
	int i;

	envp = ft_calloc(sizeof(char **) , (envplist_num(lst) + 1));
	i = 0;
	while (lst)
	{
		envp[i] = ft_calloc(sizeof(char *) , ft_strlen(tmp) + 1);
		tmp = ft_strjoin(lst->key, "=");
		envp[i] = ft_strjoin(tmp, lst->value);
		free(tmp);
		i++;
		lst = lst->next;
	}
	return (envp);
}
char *join_path(char *path, char *cmd)
{
	char *tmp;
	
	tmp = path;
	path = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = path;
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return path;
}

int find_cmd_path(t_envp *envp, t_cmd *cmd)
{
	int i;
	char **path;
	if (cmd->cmd[0] && ft_strchr(cmd->cmd[0], '/'))
	{
		if (access(cmd->cmd[0], F_OK) == 0)
			print_error(cmd->cmd[0], "Permission denied");
		else
			print_error(cmd->cmd[0], "No such file or directory");
		return (1);
	}
	while(envp)
	{
		if (ft_strncmp(envp->key, "PATH", 5) == 0)
		{
			path = ft_split(envp->value, ':');
			i = 0;
			while (path[i])
			{
				path[i] = join_path(path[i],cmd->cmd[0]);
				if (access(path[i], X_OK) == 0)
				{
					cmd->cmd[0] = ft_strdup(path[i]);
					free(path[i]);
					return (0);
				}
				free(path[i]);
				i++;
			}
		}
		envp = envp->next;
	}
	return (1);
}

int	cmd_path(t_main *main, t_cmd *cmd)
{
	t_envp *envp;
	envp = main->envp_list;
	if (cmd->cmd[0] && ft_strchr(cmd->cmd[0], '/'))
	{
		print_error(cmd->cmd[0], "No such file or directory");
		return (1);
	}
	if (find_cmd_path(envp, cmd) == 0)
		return (0);
	print_error(cmd->cmd[0], "command not found");
	return (1);
}
int single_builtin(t_main *main, t_cmd *cmd)
{
	if (cmd->infile)
	{
		if (cmd->infile_fd < 0)
		{
			print_error(cmd->infile, "No such file or directory");
			return(1);
		}
		dup2(cmd->infile_fd, 0);
	}
	close(cmd->infile_fd);
	if (cmd->outfile)
	{
		if (cmd->outfile_fd < 0)
		{
			print_error(cmd->outfile, "No such file or directory");
			return(1);
		}
		dup2(cmd->outfile_fd, 1);
	}
	close(cmd->outfile_fd);
	exit_code = do_builtin(main->cmd_list, main);
	return (0);
}
int set_input(t_main *main, t_cmd *cmd)
{
	if (main->fd_tmp > 0)
	{
		dup2(main->fd_tmp, 0);
	}
	close(main->fd_tmp);
	if (cmd->infile)
	{
		if (cmd->infile_fd < 0)
		{
			print_error(cmd->infile, "No such file or directory");
			return (1);
		}
		dup2(cmd->infile_fd, 0);
	}
	close(cmd->infile_fd);
	if (cmd->here_doc)
	{
		cmd->here_doc_fd = open(cmd->here_doc,O_RDONLY);
		dup2(cmd->here_doc_fd, 0);
		close(cmd->here_doc_fd);
	}
	return (0);
}

int set_output(t_cmd *cmd)
{
	if (cmd->fd[1] != -1)
	{
		dup2(cmd->fd[1], 1);
	}
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	if (cmd->outfile)
	{
		if (cmd->outfile_fd < 0)
		{
			print_error(cmd->outfile, "No such file or directory");
			return (1);
		}
		dup2(cmd->outfile_fd, 1);
	}
	close(cmd->outfile_fd);
	return (0);
}
void cmd_sig_handler(int signum)
{
	printf("\n\033[s");
	(void)signum;
	exit(0);
}
int set_cmd(t_main *main, t_cmd *cmd)
{
	struct stat buf;

	if (access(cmd->cmd[0], X_OK) == 0)
	{
		stat(cmd->cmd[0], &buf);
		if (S_ISDIR(buf.st_mode) != 0)
		{
			print_error(cmd->cmd[0], "is a directory");
			return (1);
		}
	}
	if (access(cmd->cmd[0], F_OK) != 0)// 파일 존재안할때
		if (cmd_path(main, cmd) == 1)
			return (1);
	if (access(cmd->cmd[0], X_OK) != 0)//파일 실행권한 여부 /성공:0 / 실패 :-1
	{
		ft_putstr_fd(cmd->cmd[0],2);
		perror(" ");
	}
	return (0);
}
void close_multiple_fd(t_main *main, t_cmd *cmd)
{
	close(main->fd_tmp);
	main->fd_tmp = dup(cmd->fd[0]);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	close(cmd->infile_fd);
	close(cmd->outfile_fd);
}

int multiple_cmd(t_main *main, t_cmd *cmd)
{
	struct stat buf;
	
	cmd->child = fork();
	if (cmd->child == 0)
	{
		sig_init(CMD);
		if (set_input(main, cmd) == 1 || set_output(cmd) == 1)
		{
			main->exit_state = 1;
			exit(1);
		}
		if (check_builtin(cmd) == 0)
		{
			main->exit_state = do_builtin(cmd, main);
			exit(0);
		}
		if (access(cmd->cmd[0], X_OK) == 0)
		{
			stat(cmd->cmd[0], &buf);
			if (S_ISDIR(buf.st_mode) != 0)
			{
				print_error(cmd->cmd[0], "is a directory");
				exit(1);
			}
		}
		if (access(cmd->cmd[0], X_OK) != 0)
			if (cmd_path(main, cmd) == 1)
				exit(127);
/*		if (access(cmd->cmd[0], X_OK) != 0)
		{
			ft_putstr_fd(cmd->cmd[0],2);
			perror(" ");
		}
		*/
		// if (set_cmd(main, cmd) != 0)
		// 	exit(1);
		execve(cmd->cmd[0], cmd->cmd, make_envp_arr(main->envp_list));
		exit(0);
	}
	close_multiple_fd(main, cmd);
	return (0);
}
void cmd_exit_process(t_main *main)
{
	char *temp;

	while(wait(&main->exit_state) > 0)
		;
	if((WIFSIGNALED(main->exit_state)))
	{
		temp = ft_itoa( WTERMSIG(main->exit_state));
		if (WTERMSIG(main->exit_state) == 3)
		{
			exit_code = 131;
			ft_putstr_fd("Quit: ",2);
			ft_putstr_fd(temp,2);
			free(temp);
		}
		else
			exit_code = 130;
		ft_putstr_fd("\n",2);
	}
	else
		exit_code = WEXITSTATUS(main->exit_state);
	dup2(main->std[0],0);
	dup2(main->std[1],1);
	sig_init(INIT);
}
void sig_init(int option)
{
	if (option == INIT)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == CMD)
	{
		signal(SIGINT, cmd_sig_handler);
		signal(SIGQUIT, cmd_sig_handler);
	}
	else if (option == HERE)
	{
		signal(SIGINT, here_doc_sigint_handler);
		signal(SIGQUIT, here_doc_sigquit_handler);
	}
	else if(option == IGN)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
int do_cmd(t_main *main)
{
	t_cmd *cmd;
	int i;

	i = 0;
	cmd = main->cmd_list;
	main->cmd_list_num = cmdlist_num(cmd);
	if (main->cmd_list_num <= 1 && check_builtin(main->cmd_list) == 0)
	{
		exit_code = single_builtin(main, cmd);
		dup2(main->std[0],0);
		dup2(main->std[1],1);
		return (0);
	}
	while (i < main->cmd_list_num)
	{
		sig_init(IGN);
		if (cmd && i + 1 < main->cmd_list_num)
			if (pipe(cmd->fd) == -1)
				return (1);
		multiple_cmd(main, cmd);
		i++;
		cmd = cmd->next;
	}
	cmd_exit_process(main);
	return (0);
} 
