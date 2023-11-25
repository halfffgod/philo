/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:24:38 by nbadalia          #+#    #+#             */
/*   Updated: 2023/11/09 17:37:49 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const	char *str)
{
  int	n;
  int	sign;
  int	i;

  n = 0;
  i = 0;
  sign = 1;
  while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
    || str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
    i++;
  if (str[i] == '-')
  {
    sign = -1;
    i++;
  }
  else if (str[i] == '+')
    i++;
  while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
  {
    n = n * 10 + (str[i] - '0');
    i++;
  }
  return (sign * n);
}

int	is_digit(int a)
{
  if (a >= '0' && a <= '9')
    return (1);
  return (0);
}

int	is_num(char **str)
{
  int	i;
  int	j;

  i = 1;
  while (str[i])
  {
    j = 0;
    while (str[i][j])
    {
      if (!is_digit(str[i][j]))
        return (1);
      j++;
    }
    i++;
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
  {
    ac = 6;
    if(av[5] == 0)
    {
      errors(5);
      return(0);
    }
  }
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