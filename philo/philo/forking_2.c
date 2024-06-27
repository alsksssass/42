/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:36:35 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/13 16:37:02 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	philo_free(t_main *main)
{
	free(main->human);
	free(main->fork_arr);
	pthread_mutex_destroy(main->flags);
	free(main->flags);
	free(main->philo);
	pthread_mutex_destroy(main->fork);
	free(main->fork);
	pthread_mutex_destroy(main->death_note);
	free(main->death_note);
	pthread_mutex_destroy(main->print);
	free(main->print);
}

t_fork	find_fork(t_philo *philo)
{
	int		num;
	t_fork	send;

	num = philo->num;
	send.r_num = num - 2;
	send.l_num = num - 1;
	if (num == 1)
		send.r_num = philo->main->num_philo - 1;
	return (send);
}

void	add_food(t_philo *philo)
{
	pthread_mutex_t	*flags;

	flags = philo->main->flags;
	pthread_mutex_lock(flags);
	philo->main->food += 1;
	pthread_mutex_unlock(flags);
}

int	useable_fork(t_philo *philo, int num)
{
	pthread_mutex_t	*note;
	pthread_mutex_t	*fork;

	fork = philo->main->fork;
	note = (philo->main->death_note) + num;
	pthread_mutex_lock(note);
	if (philo->main->fork_arr[num] == 0)
	{
		pthread_mutex_lock(fork + (num));
		philo->main->fork_arr[num] = 1;
		if (check_live(philo) == 0)
			print_message(philo, FORK);
		pthread_mutex_unlock(note);
		return (0);
	}
	pthread_mutex_unlock(note);
	return (1);
}
