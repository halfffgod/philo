/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:24:30 by nbadalia          #+#    #+#             */
/*   Updated: 2023/11/09 17:42:07 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				x_eaten;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread_id;
	long long		t_last_meal;
	struct s_life	*life;

}	t_philo;

typedef struct s_life
{
	int				nb_philo;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				nb_eat;
	int				died;
	int				all_eaten;
	long long		first_timestamp;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[201];
	pthread_mutex_t	writing;
	pthread_mutex_t	died_mtx;
	pthread_mutex_t	x_ate_mtx;
	pthread_mutex_t	all_ate_mtx;
	t_philo			philo[201];
}	t_life;

int			ft_atoi(const	char *str);
int			checking_args(char **av);
int			init_all(t_life *life, char **argv);
void		errors(int i);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_life *rules);
void		action_print(t_life *rules, int id, char *string);
void		philo_eat(t_philo *philo);
int			living(t_life *life);
void		one_philo_case(t_life *life, t_philo *philo);
int			is_dead(t_life *life);
int			get_died_flag(t_life *r);
void		death_checker(t_life *r, t_philo *p);

#endif
