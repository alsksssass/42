/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:37:39 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/16 14:45:26 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_temp(t_main *main)
{
	char	*msg;
	size_t	size_name;

	size_name = ft_strlen(main->argv[2]);
	main->o_f = open(main->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		ft_putstr_fd("pipex: here_doc >", 1);
		msg = get_next_line(STDIN_FILENO);
		if (size_name == ft_strlen(msg) - 1)
		{
			if (ft_strncmp(main->argv[2], msg, size_name) == 0)
				break ;
		}
		write(main->o_f, msg, ft_strlen(msg));
		free(msg);
		if (!msg)
			break ;
	}
	close(main->o_f);
}

void	make_pipe(t_main *main, int c_count)
{
	if (c_count + 1 < main->c_cmd)
	{
		if (pipe(main->fd) == -1)
			exit(1);
	}
}

void	child_process(t_main *main)
{
	t_cmd	cmd;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		if (set_fd(main, main->c_count, main->fd) == 1)
			exit(0);
		cmd = cmd_checker(main, (main->c_count) + 2);
		if (cmd.error == 127)
			exit(main->error);
		execve(cmd.path_command, cmd.command, main->envp);
		exit(main->error);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_main	main;

	if (parsing(&main, argc, argv, envp))
		exit(1);
	while (main.c_count < main.c_cmd)
	{
		make_pipe(&main, main.c_count);
		child_process(&main);
		close(main.old_fd);
		main.old_fd = dup(main.fd[0]);
		close(main.fd[0]);
		close(main.fd[1]);
		main.c_count++;
	}
	while (main.w_count < main.c_cmd)
	{
		waitpid(-1, &main.state, WUNTRACED);
		if (main.state != 0)
			exit(WEXITSTATUS(main.state));
		main.w_count++;
	}
	exit(0);
}
