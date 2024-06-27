/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:29:52 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/05 16:59:34 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_set(t_main *main)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*flags;
	pthread_mutex_t	*death_note;
	t_philo			*human;
	int				i;

	i = 0;
	human = main->human;
	fork = main->fork;
	death_note = main->death_note;
	flags = main->flags;
	pthread_mutex_init(flags, 0);
	while (i < main->num_philo)
	{
		ft_bzero(human, sizeof(t_philo));
		pthread_mutex_init(death_note++, 0);
		pthread_mutex_init(fork++, 0);
		main->fork_arr[i] = 0;
		human->num = i + 1;
		human->main = main;
		human++;
		i++;
	}
}

static void	even(t_philo *philo)
{
	while (1)
	{
		if (check_fork(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
			break ;
		usleep(200);
	}
}

static void	odd(t_philo *philo)
{
	long long	s_time;
	long long	n_time;
	long long	g_time;

	s_time = c_time();
	g_time = (philo->main->food_philo / 2);
	while (1)
	{
		n_time = c_time();
		if (n_time - s_time >= g_time)
			break ;
		if (check_live(philo) == 1)
			return ;
		usleep(200);
	}
	while (1)
	{
		if (check_fork(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
			break ;
		usleep(200);
	}
}

void	*cycle(void *data)
{
	t_philo	*philo;

	philo = data;
	report_eat(philo);
	if ((philo->num) % 2 == 0)
		even(philo);
	else
		odd(philo);
	pthread_exit((void *)1);
}

long long	now_time(t_philo *philo)
{
	long long	time;
	long long	now_time;

	now_time = c_time();
	time = now_time - philo->main->start_time;
	return (time);
}
