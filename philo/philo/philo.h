/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:48:10 by sabyun            #+#    #+#             */
/*   Updated: 2024/02/13 16:31:23 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SLEEP 0x01
# define FORK 0x02
# define EAT 0x04
# define THINK 0x08

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
}					t_philo;

typedef struct s_main
{
	long long		num_philo;
	long long		life_philo;
	long long		food_philo;
	long long		sleep_philo;
	long long		must_eat_philo;
	int				end_flags;
	long long		start_time;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	int				*fork_arr;
	int				food;
	int				print_msg;
	pthread_mutex_t	*death_note;
	pthread_mutex_t	*flags;
	pthread_mutex_t	*print;
	t_philo			*human;
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
void				table_set(t_main *main);
void				philo_free(t_main *main);
int					check_num(t_main *main);
void				*cycle(void *data);
long long			now_time(t_philo *philo);
int					checking(t_philo *philo, int num);
int					check_fork(t_philo *philo);
t_fork				find_fork(t_philo *philo);
int					useable_fork(t_philo *philo, int num);
void				report_eat(t_philo *philo);
void				add_food(t_philo *philo);
long long			c_time(void);
int					check_note(t_philo *philo);
int					check_live(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					print_message(t_philo *philo, int message);
int					eating(t_philo *philo);
int					is_num(char **str);
int					ft_isdigit(int str);
#endif
