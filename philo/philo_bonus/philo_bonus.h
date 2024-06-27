/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:55:09 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/05 17:14:54 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num;
	int				dead;
	long long		last_eat;
	int				num_eat;
	int				num_think;
	long long		time_life;
	long long		real_time;
	struct s_main	*main;
	pthread_mutex_t	*note;
	pthread_t		whatch;
}					t_philo;

typedef struct s_main
{
	long long		num_philo;
	long long		life_philo;
	long long		food_philo;
	long long		sleep_philo;
	long long		must_eat_philo;
	long long		end_flags;
	long long		start_time;
	int				*pid_arr;
	struct s_philo	*human;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*food;
	sem_t			*kill;
}					t_main;
typedef struct s_fork
{
	int				r_num;
	int				l_num;
}					t_fork;
long long			ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
char				*ft_strdup(const char *s1);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
long long			c_time(void);
long long			now_time(t_philo *philo);
int					check_note(t_philo *philo);
void				starting(t_philo *philo);
int					forking(t_philo *philo);
int					sleeping(t_philo *philo);
void				living(t_main *main);
int					check_num(t_main *main);
void				killer_summon(t_main *main);
void				checker_summon(t_main *main);
void				free_function(t_main *main);
int					is_num(char **str);
int					ft_isdigit(int str);
#endif
