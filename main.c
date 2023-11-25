/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:23:46 by nbadalia          #+#    #+#             */
/*   Updated: 2023/11/09 17:34:09 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_life	life;
	
	if (ac != 5 && ac != 6)
	{
		errors(2);
		return (0);
	}
	init_all(&life, av);
	// for(int i = 0; i < life.nb_philo; i++)
	// {
	// 	printf("todo");
	// 	printf("%d\n", life.philo[i].id);
	// }
	//philo_eat(life.philo);
	living(&life);
	return (0);
}
