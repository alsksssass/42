#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "pipe.h"

char **get_path(t_main *main)
{
	char **save;
	char *path;
	char **send;
	int i;

	i = 0;
	save = main->envp;
	send = 0;
	while(save[i])
	{
		path = ft_strnstr(save[i],"PATH=",sizeof(save[i]));
		if (path)
			break ;
		i++;
	}
	send = ft_split(path+5,':');
	return (send);
}
int check_here_doc (char **argv)
{
	if (ft_strncmp(argv[1],"here_doc",sizeof(argv[1]))==0)
		return 1;
	else
		return 0;
}
int parsing(t_main *main, int argc, char **argv, char **envp)
{
	ft_bzero(&main,sizeof(main));
	if (argc < 5)
		return 1;
	else
	{
		main->argv = argv;
		main->here_doc = check_here_doc(argv);
		if (main->here_doc == 1)
			main->file_name = "./.temp.txt";
		else
			main->file_name = argv[1]; 
		main->argc = argc;
		main->envp = envp;
		main->path = get_path(main);
		main->c_cmd = argc- (3 + main->here_doc);
	}
	return 0;
}
char *find_cmd(t_main *main, char *cmd)
{
	char **temp;
	char *tmp;
	char *checker;
	int i;

	i = 0;
	temp = main->path;
	checker = 0;
	while (temp[i])
	{
		checker = ft_strjoin(temp[i],"/");
		tmp = checker;
		checker = ft_strjoin(checker,cmd);
		if (tmp)
			free(tmp);
		if (access(checker, X_OK) == 0)
			return (checker);
		else
			free(checker);
		i++;
	}
	return (0);
}
void free_malloc(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
}
t_cmd cmd_checker(t_main *main, int num)
{
	t_cmd send;
	
	ft_bzero(&send,sizeof(send));
	send.command = ft_split(main->argv[num+main->here_doc], ' ');
	send.path_command = send.command[0];
	if (access(send.command[0], X_OK) ==0)
		return(send);
	else
	{
		send.path_command = find_cmd(main,send.path_command);
		if (send.path_command == 0)
			error_cmd(main,127);
	}
	return send;
}
int open_fd(t_main *main, int *fd)
{
	main->o_f = open(main->file_name,O_RDONLY);
	if (main->o_f == -1)
	{
		error_cmd(main,-2);
		return 1;
	}
	if (dup2(main->o_f,STDIN_FILENO)==-1)
		return 1;
	if (dup2(fd[1],STDOUT_FILENO) == -1)
		return 1;
	close(main->o_f);
	if (main->here_doc == 1)
		unlink(main->file_name);
	close(fd[0]);
	close(fd[1]);
	return 0;
}
int write_fd(t_main *main, int *fd)
{
	if (main->here_doc == 0)
		main->w_f = open(main->argv[main->argc-1],\
				O_WRONLY | O_CREAT | O_TRUNC , 0666);
	else
		main->w_f = open(main->argv[main->argc-1],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (main->w_f == -1)
	{
		error_cmd(main,-1);
		return 1;
	}
	if (dup2(main->old_fd,STDIN_FILENO) == -1)
		return 1;
	if (dup2(main->w_f,STDOUT_FILENO) == -1)
		return 1;
	close(main->w_f);
	close(fd[0]);
	close(fd[1]);
	return 0;
}
int nomal_fd(t_main *main, int *fd)
{
	if (dup2(main->old_fd, STDIN_FILENO) == -1)
		return 1;
	if (dup2(fd[1],STDOUT_FILENO) == -1)
		return 1;
	close(fd[0]);
	close(fd[1]);
	return 0;
}

int set_fd (t_main *main, int i, int *fd)
{

	if (i == 0)
		return open_fd(main,fd);
	else if (i == main->c_cmd - 1)
		return write_fd(main,fd);
	else
		return nomal_fd(main,fd);

}
void error_cmd(t_main *main, int error)
{
	if (error == 127)
		ft_putstr_fd("pipex: command not found\n",2);
	if (error == -1 || error == -2)
	{
		ft_putstr_fd("pipex: ",2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		if (error == -1)
			ft_putstr_fd(main->argv[main->argc-1],2);
		else
			ft_putstr_fd(main->file_name,2);
		ft_putstr_fd("\n",2);
	}
	main->error = error;
}
void make_temp(t_main *main)
{
	char *msg;
	size_t size_name;

	size_name = ft_strlen(main->argv[2]);
	main->o_f = open(main->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while(1)
	{
		ft_putstr_fd("pipex: here_doc >",1);
		msg = get_next_line(0);
		if(size_name == ft_strlen(msg)-1)
		{
			if (ft_strncmp(main->argv[2],msg,size_name) == 0)
				break;
		}
		write(main->o_f,msg,ft_strlen(msg));
	}
	close(main->o_f);
}
void here_doc_part (t_main *main)
{
	if (main->here_doc == 0)
		return;
	else
		make_temp(main);
}
void make_pipe (t_main *main, int c_count)
{
		if (c_count + 1 < main->c_cmd)
		{
			if (pipe(main->fd) == -1)
				exit(1);
		}
}
void child_process(t_main *main)
{
	t_cmd cmd;
	pid_t child;

	child = fork();
	if (child == 0)
	{
		if (set_fd(main,main->c_count,main->fd) == 1)
			exit(0);
		cmd = cmd_checker(main,(main->c_count) + 2);
		if (cmd.error == 127)
			exit(main->error);
		execve(cmd.path_command, cmd.command, main->envp);
		exit(main->error);
	}
}
int main (int argc, char **argv,char *envp[])
{
	t_main main;

	if (parsing(&main,argc,argv,envp))
		exit(1);
	here_doc_part(&main);
	while(main.c_count<main.c_cmd)
	{
		make_pipe (&main,main.c_count);
		child_process(&main);
		close(main.old_fd);
		main.old_fd = dup(main.fd[0]);
		close(main.fd[0]);
		close(main.fd[1]);
		main.c_count++;
	}
	while (main.w_count < main.c_cmd)
	{
		waitpid(-1,&main.state, WUNTRACED);
		if (main.state!=0)
			exit(WEXITSTATUS(main.state));
		main.w_count++;
	}
	exit(0);
}
