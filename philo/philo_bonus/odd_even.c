/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_even.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:46:33 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/05 10:25:53 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*whatcher(void *data)
{
	long long	time;
	t_philo		*philo;

	philo = data;
	while (1)
	{
		time = c_time();
		pthread_mutex_lock(philo->note);
		if (time - philo->last_eat >= philo->main->life_philo)
			break ;
		pthread_mutex_unlock(philo->note);
		usleep(200);
	}
	pthread_mutex_unlock(philo->note);
	sem_wait(philo->main->print);
	printf("%lld %d died\n", now_time(philo), philo->num + 1);
	sem_post(philo->main->kill);
	pthread_exit((void *)1);
}

static void	odd(t_philo *philo)
{
	pid_t	child;

	child = fork();
	philo->main->pid_arr[philo->num] = child;
	if (child == 0)
	{
		starting(philo);
		philo->last_eat = c_time();
		pthread_create(&philo->whatch, NULL, whatcher, (void *)philo);
		usleep((philo->main->food_philo / 2) * 1000);
		while (1)
		{
			if (forking(philo) == 1)
				break ;
			if (sleeping(philo) == 1)
				break ;
			usleep(200);
		}
		sem_post(philo->main->kill);
		exit(0);
	}
}

static void	even(t_philo *philo)
{
	pid_t	child;

	child = fork();
	philo->main->pid_arr[philo->num] = child;
	if (child == 0)
	{
		starting(philo);
		philo->last_eat = c_time();
		pthread_create(&philo->whatch, NULL, whatcher, (void *)philo);
		while (1)
		{
			if (forking(philo) == 1)
				break ;
			if (sleeping(philo) == 1)
				break ;
			usleep(200);
		}
		sem_post(philo->main->kill);
		exit(0);
	}
}

static void	philo_summon(t_philo *philo)
{
	int	num;

	num = philo->num;
	if (num % 2 == 0)
		even(philo);
	else
		odd(philo);
}

void	living(t_main *main)
{
	int	i;

	i = 0;
	main->start_time = c_time();
	while (i < main->num_philo + 2)
	{
		if (i < main->num_philo)
			philo_summon((main->human) + i);
		else if (i == main->num_philo)
			checker_summon(main);
		else if (i == main->num_philo + 1)
			killer_summon(main);
		i++;
		usleep(200);
	}
}
