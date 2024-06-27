#include "minishell.h"
/*
void env_process(t_main *main)
{
	int i;
	i = 0;

	while(main->cmd[i])
	{
		if (ft_strcmp(main->cmd[i],"$") == 1)
			change_env(main,main->cmd[i]);	
	}
}
*/
int echo(char **cmd)
{
	int i;
	int option;

	option = 0;
	i = 1;
	if (!cmd[i])
	{
		ft_putstr_fd("\n",1);
		return (0);
	}
	while(1)
	{
		if(ft_strncmp(cmd[i],"-n",2) != 0)
			break;
		if(ft_strncmp(cmd[i],"-n",2) == 0)
		{
			option = 1;
			i++;
		}
	}
	while(cmd[i])
	{
		ft_putstr_fd(cmd[i],1);
		i++;
		if(cmd[i])
			ft_putstr_fd(" ",1);
	}
	if (option == 0)
		ft_putstr_fd("\n",1);
	return (0);
}

int pwd(t_main *main)
{
    char path[4096];

    if (getcwd(path, sizeof(path))) 
        printf("%s\n", path);
	else if(main->save_pwd)
	{
		ft_putstr_fd(main->save_pwd ,1);	
		ft_putstr_fd("\n" ,1);	
	}
	else
	{
		print_error("getcwd", "cannot access parent directories");
        return (1);
    }
	return (0);
}

int cd(t_main *main, char *cmd)
{
    char path[4096];
    char pwd[4096];
	char *old_pwd;
	
    if (chdir(cmd) != 0)
	{
        if(getcwd(pwd,sizeof(pwd)))
			old_pwd = ft_strjoin(pwd,cmd);
		else
			old_pwd = main->save_pwd;
		if (chdir(old_pwd) != 0)
		{
			free(old_pwd);
			print_error(cmd, "no such file or directory");
       		return (1);
		}
		free(old_pwd);
    }
	if (getcwd(path, sizeof(path))) 
	{
		old_pwd = get_env(main->envp_list,ft_strdup("PWD"));
		check_already_add(main,ft_strdup("OLDPWD"),old_pwd);
		check_already_add(main,ft_strdup("PWD"),ft_strdup(path));
		main->save_pwd = ft_strdup(path);
	}
	else
	{
		old_pwd = main->save_pwd;
		print_error("cd", "error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
		main->save_pwd = ft_strjoin(main->save_pwd,"/..");
		free(old_pwd);
	}
	return (0);
}

int unset_built(t_main *main, char **cmd)
{
	int i;

	i = 1;

	while(cmd[i])
	{
		delete_env(main,cmd[i]);
		i++;
	}
	return (0);
}

int export_built(t_main *main, char **cmd)
{
	int i;
	
	i = 1;

	if (!cmd[i])
	{
		print_envp(main,0);
	}
	while(cmd[i])
	{
		make_envp(main,cmd[i]);
		i++;
	}
	return (0);
}

int check_builtin(t_cmd *list)
{
	char **cmd;

	cmd = list->cmd;
	if (!list || !cmd || !*cmd)
		return 1;
	if (ft_strncmp(cmd[0],"echo",5) == 0)
		return 0;
	else if (ft_strncmp(cmd[0],"pwd",4) == 0)
		return 0;
	else if (ft_strncmp(cmd[0],"cd",3) == 0)
		return 0;
	else if (ft_strncmp(cmd[0],"exit",5) == 0)
		return 0;
	else if (ft_strncmp(cmd[0],"export",7) == 0)
		return 0;
	else if (ft_strncmp(cmd[0],"unset",6) == 0)
		return 0;
	else if (ft_strncmp(cmd[0],"env",4) == 0)
		return 0;
	return 1;
}

int do_builtin(t_cmd *list, t_main *main)
{

	char **cmd;

	cmd = list->cmd;
	if (!list || !cmd || !*cmd)
		return 1;
	else if (ft_strncmp(cmd[0],"echo",5) == 0)
		return (echo(cmd));
	else if (ft_strncmp(cmd[0],"pwd",4) == 0)
		return (pwd(main));
	else if (ft_strncmp(cmd[0],"cd",3) == 0)
		return (cd(main,cmd[1]));
	else if (ft_strncmp(cmd[0],"exit",5) == 0)
		return (exit_num(cmd));
	else if (ft_strncmp(cmd[0],"export",7) == 0)
		return (export_built(main,cmd));
	else if (ft_strncmp(cmd[0],"unset",6) == 0)
		return (unset_built(main,cmd));
	else if (ft_strncmp(cmd[0],"env",4) == 0)
	{
		print_envp(main,1);
		return (1);
	}
	return 0;
}
