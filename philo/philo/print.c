/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:09:23 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/13 16:37:48 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	messages(t_philo *philo, int message)
{
	pthread_mutex_lock(philo->main->print);
	if (message & FORK)
		printf("%lld %d has taken a fork\n", now_time((philo)), philo->num);
	else if (message & SLEEP)
		printf("%lld %d is sleeping\n", now_time(philo), philo->num);
	else if (message & EAT)
		printf("%lld %d is eating\n", now_time(philo), philo->num);
	else if (message & THINK)
		printf("%lld %d is thinking\n", now_time(philo), philo->num);
	pthread_mutex_unlock(philo->main->print);
}

int	print_message(t_philo *philo, int message)
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
	else
		messages(philo, message);
	pthread_mutex_unlock(flags);
	return (0);
}

int	eating(t_philo *philo)
{
	long long	time;
	long long	n_time;

	time = c_time();
	while (1)
	{
		n_time = c_time();
		if ((n_time - time >= (philo->main->food_philo)))
			break ;
		if (check_live(philo) == 1)
			return (1);
		usleep(200);
	}
	return (0);
}

int	ft_isdigit(int str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

int	is_num(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
