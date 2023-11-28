#include "philo.h"

long long	timestamp(void)
{
  struct timeval	t;

  gettimeofday(&t, NULL);
  return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
  return (pres - past);
}

// void get_died_status(t_life *life, int i)
// {
// 	pthread_mutex_lock(&(r->died_mtx));////////
// 	life->died = i;
// 	pthread_mutex_unlock(&(r->died_mtx));////////

// }

void		smart_sleep(long long time, t_life *rules)
{
  long long igh;

  igh = timestamp();
  while (!(rules->died))
  {
    if (time_diff(igh, timestamp()) >= time)
      break ;
    usleep(50);
  }
}


void		action_print(t_life *rules, int id, char *string)
{
  pthread_mutex_lock(&(rules->writing));
  if (!(rules->died))
  {
    printf("%lli ", timestamp() - rules->first_timestamp);
    printf("Philo №%i ", id + 1);
    printf("%s\n", string);
  }
  pthread_mutex_unlock(&(rules->writing));
  return ;
}