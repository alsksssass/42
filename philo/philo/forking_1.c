/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:36:39 by sabyun            #+#    #+#             */
/*   Updated: 2024/01/29 21:40:00 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	return_fork(t_philo *philo, int num)
{
	pthread_mutex_t	*note;

	note = (philo->main->death_note) + num;
	pthread_mutex_lock(note);
	philo->main->fork_arr[num] = 0;
	pthread_mutex_unlock(note);
}

int	checking(t_philo *philo, int num)
{
	while (1)
	{
		if (check_live(philo) == 1)
			break ;
		if (useable_fork(philo, num) == 0)
			return (0);
		usleep(200);
	}
	return (1);
}

static int	while_forking(t_philo *philo, t_fork pick)
{
	pthread_mutex_t	*fork;

	fork = philo->main->fork;
	if (checking(philo, pick.r_num) == 1)
		return (1);
	if (checking(philo, pick.l_num) == 1)
	{
		pthread_mutex_unlock(fork + (pick.r_num));
		return (1);
	}
	report_eat(philo);
	print_message(philo, EAT);
	return (0);
}

static void	replace_fork(t_philo *philo, t_fork pick)
{
	pthread_mutex_t	*fork;

	fork = philo->main->fork;
	return_fork(philo, pick.r_num);
	return_fork(philo, pick.l_num);
	pthread_mutex_unlock(fork + (pick.r_num));
	pthread_mutex_unlock(fork + (pick.l_num));
}

int	check_fork(t_philo *philo)
{
	t_fork	pick;

	pick = find_fork(philo);
	if (while_forking(philo, pick) == 1)
		return (1);
	if (eating(philo) == 1)
	{
		replace_fork(philo, pick);
		return (1);
	}
	(philo->num_eat)++;
	if (philo->num_eat == philo->main->must_eat_philo
		&& philo->main->must_eat_philo != 0)
		add_food(philo);
	replace_fork(philo, pick);
	return (0);
}
