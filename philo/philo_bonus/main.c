/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:56:53 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/08 17:59:39 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	table_set(t_main *main)
{
	t_philo	*human;
	int		i;

	i = 0;
	while (i < main->num_philo)
	{
		human = (main->human) + i;
		ft_bzero(human, sizeof(t_philo));
		human->note = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(human->note, 0);
		human->num = i;
		human->main = main;
		i++;
	}
}

void	set_table(t_main *main, int argc, char **argv)
{
	ft_bzero(main, sizeof(t_main));
	main->num_philo = ft_atoi(argv[1]);
	main->life_philo = ft_atoi(argv[2]);
	main->food_philo = ft_atoi(argv[3]);
	main->sleep_philo = ft_atoi(argv[4]);
	if (argc == 6)
		main->must_eat_philo = ft_atoi(argv[5]);
	else
		main->must_eat_philo = 0;
	main->human = malloc((main->num_philo) * sizeof(t_philo));
	main->pid_arr = malloc(((main->num_philo) + 2) * sizeof(int));
	sem_unlink("/fork");
	main->fork = sem_open("/fork", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR,
			main->num_philo);
	sem_unlink("/food");
	main->food = sem_open("/food", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	sem_unlink("/kill");
	main->kill = sem_open("/kill", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	sem_unlink("/print");
	main->print = sem_open("/print", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	table_set(main);
}

void	killer_summon(t_main *main)
{
	pid_t	child;
	int		i;

	child = fork();
	main->pid_arr[main->num_philo + 1] = child;
	if (child == 0)
	{
		i = 0;
		sem_wait(main->kill);
		while (i < (main->num_philo) + 1)
		{
			kill(main->pid_arr[i], SIGTERM);
			i++;
		}
		exit(0);
	}
}

void	checker_summon(t_main *main)
{
	pid_t	child;
	int		i;

	child = fork();
	main->pid_arr[main->num_philo] = child;
	if (child == 0)
	{
		i = 0;
		while (i < main->num_philo)
		{
			sem_wait(main->food);
			i++;
		}
		sem_wait(main->print);
		sem_post(main->kill);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_main	main;
	int		i;

	i = 0;
	if (!(argc >= 5 && argc <= 6))
		exit(1);
	set_table(&main, argc, argv);
	if (check_num(&main) == 1)
	{
		printf("Invalid argument\n");
		free_function(&main);
		exit(1);
	}
	living(&main);
	while (i < main.num_philo + 1)
	{
		wait(0);
		i++;
	}
	free_function(&main);
	exit(0);
}
