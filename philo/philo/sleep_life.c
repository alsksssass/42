/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:38:34 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/29 21:43:28 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	c_time(void)
{
	struct timeval	timeval_time;
	long long		result;

	gettimeofday(&timeval_time, 0);
	result = (timeval_time.tv_sec * 1000) + (timeval_time.tv_usec / 1000);
	return (result);
}

void	report_eat(t_philo *philo)
{
	philo->last_eat = c_time();
}

int	check_note(t_philo *philo)
{
	long long	eat_time;
	long long	real_time;
	long long	life;

	life = (philo->main->life_philo);
	real_time = c_time();
	eat_time = philo->last_eat;
	if (real_time - eat_time >= life)
		return (1);
	return (0);
}

int	check_live(t_philo *philo)
{
	pthread_mutex_t	*flags;

	flags = philo->main->flags;
	pthread_mutex_lock(flags);
	if (philo->main->end_flags == 1
		|| philo->main->food == (philo->main->num_philo))
	{
		pthread_mutex_unlock(flags);
		return (1);
	}
	if (check_note(philo) == 1)
	{
		philo->dead = 1;
		philo->main->end_flags = 1;
		pthread_mutex_lock(philo->main->print);
		printf("%lld %d died\n", now_time((philo)), philo->num);
		pthread_mutex_unlock(philo->main->print);
		pthread_mutex_unlock(flags);
		return (1);
	}
	pthread_mutex_unlock(flags);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	long long	time;
	long long	n_time;

	time = c_time();
	if (check_live(philo) == 1)
		return (1);
	print_message(philo, SLEEP);
	while (1)
	{
		n_time = c_time();
		if (n_time - time >= (philo->main->sleep_philo))
			break ;
		if (check_live(philo) == 1)
			return (1);
		usleep(200);
	}
	print_message(philo, THINK);
	return (0);
}
