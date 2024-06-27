/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:24:27 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/08 17:57:21 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_init(pthread_t *philo, int i)
{
	pthread_t	*temp;

	temp = philo;
	while (i > 0)
	{
		ft_bzero(temp, sizeof(pthread_t));
		temp++;
		i--;
	}
}

void	make_base(t_main *main, int argc, char **argv)
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
	main->philo = malloc((main->num_philo) * sizeof(pthread_t));
	main->fork = malloc((main->num_philo) * sizeof(pthread_mutex_t));
	main->fork_arr = malloc((main->num_philo) * sizeof(int));
	main->death_note = malloc((main->num_philo) * sizeof(pthread_mutex_t));
	main->human = malloc((main->num_philo) * sizeof(t_philo));
	main->flags = malloc(sizeof(pthread_mutex_t));
	main->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->print, 0);
	pthread_init(main->philo, main->num_philo);
	table_set(main);
}

int	make_thread(t_main *main)
{
	int	thr_id;
	int	i;

	i = 0;
	while (i < main->num_philo)
	{
		thr_id = pthread_create(((main->philo) + i), NULL, cycle,
				(void *)((main->human) + i));
		if (thr_id < 0)
			return (1);
		i++;
	}
	return (0);
}

void	wait_thread(t_main *main)
{
	int		count;
	void	*state;
	int		j;

	j = 0;
	count = 0;
	while (1)
	{
		if (j > (main->num_philo) - 1)
			j = 0;
		pthread_join(main->philo[j], &state);
		if ((long)state == 1)
			count++;
		if (count == main->num_philo)
			break ;
		j++;
	}
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (!(argc >= 5 && argc <= 6))
		return (1);
	make_base(&main, argc, argv);
	if (check_num(&main) == 1 || is_num(argv) == 1)
	{
		printf("Invalid argument\n");
		philo_free(&main);
		return (1);
	}
	main.start_time = c_time();
	if (make_thread(&main) == 1)
	{
		philo_free(&main);
		return (1);
	}
	wait_thread(&main);
	philo_free(&main);
	return (0);
}
