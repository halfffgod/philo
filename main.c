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

int		main(int argc, char **argv)
    {
      (void)argc;
	  
	  t_life	life;
      int		ret;
      if ((ret = init_all(&life, argv)))
        return (5);
      if (living(&life))
        return (6);
      return (0);
    }
