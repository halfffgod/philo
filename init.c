/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:24:03 by nbadalia          #+#    #+#             */
/*   Updated: 2023/11/09 17:32:06 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutex(t_life *life)
{
	int	i;

	i = 0;
	while(i++ <= life->nb_philo)
	{
		if(pthread_mutex_init(&(life->forks[i]), NULL))
			return (1);
	}
	if(pthread_mutex_init(&(life->writing), NULL))
		return (1);
	if(pthread_mutex_init(&(life->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philoes(t_life *life)
{
	int	i;

	i = 0;
	while (i++ <= life->nb_philo)
	{
		life->philo[i].id = i;
		life->philo[i].x_eaten = 0;
		life->philo[i].left_fork_id = i;
		life->philo[i].t_last_meal = 0;
		life->philo[i].life = life;
		if (i != life->nb_philo)
			life->philo[i].right_fork_id = i + 1;
		else
			life->philo[i].right_fork_id = 1;
	}
	return (0);
}

int	checking_args(char **av)
{
	int	i;
	int	ac;

	i = 0;
	if (!av[5])
		ac = 5;
	else
		ac = 6;
	while (i < ac)
	{
		if (is_num(&av[i]))
		{
			return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	init_all(t_life *life, char **av)
{
	if (checking_args(av))
		errors(3);
	else
	{
		life->nb_philo = ft_atoi(av[1]);
		life->time_die = ft_atoi(av[2]);
		life->time_eat = ft_atoi(av[3]);
		life->time_sleep = ft_atoi(av[4]);
		rules->all_eaten = 0;
		rules->died = 0;
		if (life->nb_philo < 2 || life->nb_philo > 200)
			errors (1);
		if (av[5])
			life->nb_eat = ft_atoi(av[5]);
		else
			life->nb_eat = -1;
		if(init_mutex(life))
			errors(4);
		init_philoes(life);
	}
	return (0);
}
