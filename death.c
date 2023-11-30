/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:25:58 by nbadalia          #+#    #+#             */
/*   Updated: 2023/11/30 15:26:00 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_death(t_life *r, t_philo *p, int i)
{
	pthread_mutex_lock(&(r->meal_check));
	if (time_diff(p[i].t_last_meal, timestamp()) > r->time_die)
	{
		action_print(r, i, "is died");
		pthread_mutex_lock(&(r->died_mtx));
		r->died = 1;
		pthread_mutex_unlock(&(r->died_mtx));
	}
	pthread_mutex_unlock(&(r->meal_check));
}

void	check_all_ate(t_life *r, t_philo *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(r->x_ate_mtx));
	while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_eaten >= r->nb_eat)
		i++;
	if (i == r->nb_philo)
	{
		pthread_mutex_lock(&(r->all_ate_mtx));
		r->all_eaten = 1;
		pthread_mutex_unlock(&(r->all_ate_mtx));
	}
	pthread_mutex_unlock(&(r->x_ate_mtx));
}

void	death_checker(t_life *r, t_philo *p)
{
	int	i;

	while (!(r->all_eaten))
	{
		i = -1;
		while (++i < r->nb_philo && !(get_died_flag(r)))
		{
			check_philo_death(r, p, i);
			usleep(100);
		}
		if (get_died_flag(r))
			break ;
		check_all_ate(r, p);
	}
}
