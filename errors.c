/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:23:53 by nbadalia          #+#    #+#             */
/*   Updated: 2023/11/09 17:27:43 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	errors(int i)
{
	if (i == 1)
	{
		printf("Error:	Invalid number of philosophers:");
		printf("	the number of philosophers can't be");
		printf(" less than 2 or more than 200\n");
	}
	else if (i == 2)
		printf("Error:	Wrong amount of arguments\n");
	else if (i == 3)
	{
		printf("Error: The passing arguments can't be");
		printf(" non-numeric values or negative numbers\n");
	}
	else if (i == 4)
		printf("Error: Fatal error when intializing mutex\n");
	else if (i == 5)
		printf("Error: The number of times each_philosopher");
		printf(" must eat can't be '0'\n");	
}
