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

void	philo_eat(t_philo *philo)
    {
      t_life *life;

      life = philo->life;
      pthread_mutex_lock(&(life->forks[philo->left_fork_id]));
      action_print(life, philo->id, "has taken a fork");
      pthread_mutex_lock(&(life->forks[philo->right_fork_id]));
      action_print(life, philo->id, "has taken a fork");
      pthread_mutex_lock(&(life->meal_check));
      //pthread_mutex_lock(&(life->philosophers->t_last_meal_mtx)); /////
      action_print(life, philo->id, "is eating");
      philo->t_last_meal = timestamp();
      //pthread_mutex_unlock(&(life->philosophers->t_last_meal_mtx));/////
      pthread_mutex_unlock(&(life->meal_check));
      smart_sleep(life->time_eat, life);
      pthread_mutex_lock(&(life->x_ate_mtx));////////
      philo->x_eaten++;
      pthread_mutex_unlock(&(life->x_ate_mtx));/////////
      pthread_mutex_unlock(&(life->forks[philo->left_fork_id]));
      pthread_mutex_unlock(&(life->forks[philo->right_fork_id]));
    }

void	*p_thread(void *void_philosopher)
{
      int		i;
      t_philo	*philo;
      t_life	*life;

      i = 0;
      philo = (t_philo *)void_philosopher;
      life = philo->life;
      if (philo->id % 2)
        usleep(500);
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
    //   action_print(life, philo->id, "is sleeping");
    //   smart_sleep(life->time_sleep, life);
    //   action_print(life, philo->id, "is thinking");
    //   i++;
      return (NULL);
}

	void	exit_launcher(t_life *life, t_philo *philos)
    {
      int i;

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
    }

	void	death_checker(t_life *r, t_philo *p)
    {
      int i;

      while (!(r->all_eaten))
      {
        i = -1;
        while (++i < r->nb_philo && !(r->died))
        {
          pthread_mutex_lock(&(r->meal_check));
          if (time_diff(p[i].t_last_meal, timestamp()) > r->time_die)
          {
            action_print(r, i, "is died");
            //pthread_mutex_lock(&(r->died_mtx));////////
            r->died = 1;
            //pthread_mutex_unlock(&(r->died_mtx));/////////
          }
          pthread_mutex_unlock(&(r->meal_check));
          usleep(100);
        }
        if (r->died)
          break ;
        i = 0;
        pthread_mutex_lock(&(r->x_ate_mtx));////////
        while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_eaten >= r->nb_eat)
          i++;  
        //pthread_mutex_unlock(&(r->x_ate_mtx));////////
        if (i == r->nb_philo)
        { 
           //pthread_mutex_lock(&(r->all_ate_mtx));////////
           r->all_eaten = 1;
           //pthread_mutex_unlock(&(r->all_ate_mtx));//////
        }
       pthread_mutex_unlock(&(r->x_ate_mtx));////////
      }
    }
    
	
int		living(t_life *life)
    {
      int		i;
      t_philo	*phi;

      i = 0;
      phi = life->philo;
      life->first_timestamp = timestamp();
	  ////////////////////////////////////
	  if(life->nb_philo == 1)
	  {
	  	one_philo_case(life, life->philo);
		return(0);
	  }
	  ////////////////////////////////////
      pthread_mutex_lock(&(life->all_ate_mtx));/////////////////////////////////////////////////
      while (i < life->nb_philo)
      {
        if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
          return (1);
        ////////////////////////////////////////////////
        ////   THIS SECTION IS IMPORTANT      //////////
        /////  FOR AVOIDING DATA RACES        //////////
        ////////////////////////////////////////////////
        pthread_mutex_lock(&(life->meal_check));///////
        phi[i].t_last_meal = timestamp();
        pthread_mutex_unlock(&(life->meal_check));///////
        i++;
      }
      pthread_mutex_unlock(&(life->all_ate_mtx));///////////////////////////////////////////////
      death_checker(life, life->philo);
      exit_launcher(life, phi);
      return (0);
    }