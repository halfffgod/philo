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
	//printf("%lld", time_diff(timestamp(), timestamp() + 1));
	if (ac != 5 && ac != 6)
	{
		errors(2);
		return (0);
	}
	init_all(&life, av);
	return (0);
}
