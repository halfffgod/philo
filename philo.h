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
	pthread_mutex_t	forks[200];
	pthread_mutex_t	writing;
	t_philo			philo[200];
}	t_life;

//utils
int			ft_atoi(const	char *str);
int			checking_args(char **av);

//initialization
int			init_all(t_life *life, char **argv);
//error management
void		errors(int i);
//time
long long	get_time(void);
void		other_usleep(t_life *life, int ms);

#endif
