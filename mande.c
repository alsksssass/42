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
int parsing(t_main *main, int argc, char **argv, char **envp)
{
	if (argc == 1)
		return 1;
	else
	{
		main->command = argv;
		main->c_number = argc;
		main->cmd = ft_split(argv[2],' ');
		main->cmd2 = ft_split(argv[3],' ');
		main->envp = envp;
		main->path = get_path(main);
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

	send.command = ft_split(main->command[num], ' ');
	send.path_command = send.command[0];
	if (access(send.command[0], X_OK)==0)
		return(send);
	else
	{
		send.path_command = find_cmd(main,send.path_command);
		if (!send.path_command)
			send.error = 1;
	}
	return send;
}
int main (int argc, char **argv,char *envp[])
{
	t_main main;
	ft_bzero(&main,sizeof(main));
	if (parsing(&main,argc,argv,envp))
		return 1;
	int fd[2];
	int num;
	int state;
	int i;

	i = 0;
	t_cmd cmd;
	state = 0;
	if (pipe(fd) == -1)
		return 1;
    // fd[1] - write
    // fd[0] - read

    // 3 4
    pid_t child = fork();
    if (child == 0)
    {
		num = 2;
		cmd = cmd_checker(&main,num);
		if (cmd.error == 1)
			exit(127);
		main.o_f = open(argv[1],O_RDONLY);
        dup2(main.o_f,0);
        dup2(fd[1],1);
        close(fd[1]);
        close(fd[0]);
        execve(cmd.path_command, cmd.command, 0);
        exit(0);
    }

    child = fork();


    if (child == 0)
    {
		num = 3;
		cmd = cmd_checker(&main,num);
		if (cmd.error == 1)
			exit(127);
		main.w_f = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd[0],0);
        dup2(main.w_f,1);
        close(fd[0]);
        close(fd[1]);
        execve(cmd.path_command, cmd.command, 0);
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);

    while(i<2)
    {
        waitpid(child,&state,0);
		if (state!=0)
			exit(WEXITSTATUS(state));
		i++;
    }
}
