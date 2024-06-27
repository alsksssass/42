/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_fuc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:39:49 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/30 12:01:24 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	c_time(void)
{
	struct timeval	timeval_time;
	long long		result;

	gettimeofday(&timeval_time, 0);
	result = (timeval_time.tv_sec * 1000) + (timeval_time.tv_usec / 1000);
	return (result);
}

long long	now_time(t_philo *philo)
{
	long long	time;
	long long	now_time;

	now_time = c_time();
	time = now_time - philo->main->start_time - 2000;
	return (time);
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

void	starting(t_philo *philo)
{
	long long	time;

	while (1)
	{
		time = c_time();
		if (time - philo->main->start_time >= 2000)
			break ;
	}
}

void	free_function(t_main *main)
{
	int		i;
	t_philo	*man;

	i = 0;
	while (i < main->num_philo)
	{
		man = (main->human) + i;
		pthread_mutex_destroy(man->note);
		free(man->note);
		i++;
	}
	free(main->human);
	free(main->pid_arr);
	sem_unlink("/fork");
	sem_unlink("/food");
	sem_unlink("/kill");
	sem_unlink("/print");
	sem_close(main->fork);
	sem_close(main->print);
	sem_close(main->kill);
	sem_close(main->food);
}
