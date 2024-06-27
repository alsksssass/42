/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:43:29 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/05 10:21:55 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static long long	do_fork(t_philo *philo)
{
	long long	time;

	sem_wait(philo->main->fork);
	sem_wait(philo->main->print);
	printf("%lld %d has taken a fork\n", now_time(philo), philo->num + 1);
	sem_post(philo->main->print);
	sem_wait(philo->main->fork);
	sem_wait(philo->main->print);
	printf("%lld %d has taken a fork\n", now_time(philo), philo->num + 1);
	sem_post(philo->main->print);
	time = c_time();
	pthread_mutex_lock(philo->note);
	philo->last_eat = time;
	pthread_mutex_unlock(philo->note);
	sem_wait(philo->main->print);
	printf("%lld %d is eating\n", now_time(philo), philo->num + 1);
	sem_post(philo->main->print);
	return (time);
}

int	forking(t_philo *philo)
{
	long long	time;
	long long	n_time;

	time = do_fork(philo);
	while (1)
	{
		n_time = c_time();
		if (n_time - time >= philo->main->food_philo)
			break ;
		usleep(2000);
	}
	(philo->num_eat)++;
	if (philo->num_eat == philo->main->must_eat_philo
		&& philo->main->must_eat_philo != 0)
		sem_post(philo->main->food);
	sem_post(philo->main->fork);
	sem_post(philo->main->fork);
	return (0);
}

int	check_num(t_main *main)
{
	if (((main->num_philo) > 2147483648) || main->num_philo <= 0)
		return (1);
	if ((main->life_philo) > 2147483648 || main->life_philo < 60)
		return (1);
	if ((main->food_philo) > 2147483648 || main->food_philo < 60)
		return (1);
	if ((main->sleep_philo) > 2147483648 || main->sleep_philo < 60)
		return (1);
	if ((main->must_eat_philo) > 2147483648 || main->must_eat_philo < 0)
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	long long	time;
	long long	n_time;

	time = c_time();
	sem_wait(philo->main->print);
	printf("%lld %d is sleeping\n", now_time(philo), philo->num + 1);
	sem_post(philo->main->print);
	while (1)
	{
		n_time = c_time();
		if (n_time - time >= philo->main->sleep_philo)
			break ;
		usleep(2000);
	}
	sem_wait(philo->main->print);
	printf("%lld %d is thinking\n", now_time(philo), philo->num + 1);
	sem_post(philo->main->print);
	return (0);
}
