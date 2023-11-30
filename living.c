/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:24:16 by nbadalia          #+#    #+#             */
/*   Updated: 2023/11/09 17:24:18 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_life	*life;

	life = philo->life;
	pthread_mutex_lock(&(life->forks[philo->left_fork_id]));
	action_print(life, philo->id, "has taken a fork");
	pthread_mutex_lock(&(life->forks[philo->right_fork_id]));
	action_print(life, philo->id, "has taken a fork");
	pthread_mutex_lock(&(life->meal_check));
	action_print(life, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(life->meal_check));
	smart_sleep(life->time_eat, life);
	pthread_mutex_lock(&(life->x_ate_mtx));
	philo->x_eaten++;
	pthread_mutex_unlock(&(life->x_ate_mtx));
	pthread_mutex_unlock(&(life->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(life->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	int		i;
	t_philo	*philo;
	t_life	*life;
	int		gh;

	i = 0;
	philo = (t_philo *)void_philosopher;
	life = philo->life;
	if (philo->id % 2)
		usleep(500);
	while (!(get_died_flag(life)))
	{
		philo_eat(philo);
		pthread_mutex_lock(&(life->all_ate_mtx));
		gh = life->all_eaten;
		pthread_mutex_unlock(&(life->all_ate_mtx));
		if (gh)
			break ;
		action_print(life, philo->id, "is sleeping");
		smart_sleep(life->time_sleep, life);
		action_print(life, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_launcher(t_life *life, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < life->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < life->nb_philo)
		pthread_mutex_destroy(&(life->forks[i]));
	pthread_mutex_destroy(&(life->meal_check));
	pthread_mutex_destroy(&(life->writing));
	pthread_mutex_destroy(&(life->x_ate_mtx));
	pthread_mutex_destroy(&(life->all_ate_mtx));
	pthread_mutex_destroy(&(life->died_mtx));
}

int	living(t_life *life)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = life->philo;
	life->first_timestamp = timestamp();
	if (life->nb_philo == 1)
	{
		one_philo_case(life, life->philo);
		return (0);
	}
	pthread_mutex_lock(&(life->all_ate_mtx));
	while (i < life->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		pthread_mutex_lock(&(life->meal_check));
		phi[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(life->meal_check));
		i++;
	}
	pthread_mutex_unlock(&(life->all_ate_mtx));
	death_checker(life, life->philo);
	exit_launcher(life, phi);
	return (0);
}
