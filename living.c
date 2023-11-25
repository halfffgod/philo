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


//here must be the main solution
#include "philo.h"

void philo_eat(t_philo *philo)
{
	t_life *life;

	life = philo->life;
	pthread_mutex_lock(&(life->forks[philo->left_fork_id]));
	action_print(life, philo->id,"has taken a fork");
	pthread_mutex_lock(&(life->forks[philo->right_fork_id]));
	action_print(life, philo->id,"has taken a fork");
	pthread_mutex_lock(&(life->meal_check));
	action_print(life, philo->id,"is eating...");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(life->meal_check));
	smart_sleep(life->time_eat, life);
	(philo->x_eaten)++;
	pthread_mutex_unlock(&(life->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(life->forks[philo->right_fork_id]));

}

// int death_checker(t_philo *philo)
// {
	
// }

// void *p_thread(void *philo_void)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)philo_void;
// 	//printf("ur here ape ");
// 	if(philo->id % 2)
// 		usleep(100);
// 	philo_eat(philo);
// 	return(NULL);
// }

void	*p_thread(void *void_philosopher)
{
      int		i;
      t_philo	*philo;
      t_life	*life;

      i = 0;
      philo = (t_philo *)void_philosopher;
      life = philo->life;
      if (philo->id % 2)
        usleep(15000);
      while (!(life->died))
      {
        philo_eat(philo);
        if (life->all_eaten)
          break ;
        action_print(life, philo->id, "is sleeping");
        smart_sleep(life->time_sleep, life);
        action_print(life, philo->id, "is thinking");
        i++;
      }
      action_print(life, philo->id, "is sleeping");
      smart_sleep(life->time_sleep, life);
      action_print(life, philo->id, "is thinking");
      i++;
      return (NULL);
}


	//the main living func

void living(t_life *life)
{
	
	t_philo *philo;

	int i;
	philo = life->philo;
	i = 0;
	//printf("ur here bebe\n");
	while(i < life->nb_philo)
	{
		if((pthread_create(&(philo[i].thread_id), NULL, p_thread, &(philo[i]))))
			//printf("doing something \n");
			errors(6);
		i++;
	}
}