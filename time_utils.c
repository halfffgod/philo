#include "philo.h"
int oxormi(t_life *life);

long long	get_time(void)
{
	struct timeval		time;
	static int			c;
	static long long	start;

	if (gettimeofday(&time, NULL) != 0)
		return(-1);
	if (c == 0)
	{
		start = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		c++;
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

void	other_usleep(t_life *life, int ms)
{
	long long	time;

	time = get_time();
	while (!oxormi(life)) //i will write oxormi() func later
	{
		if (get_time() - time < ms)
			usleep(50);
		else
			break;
	}
}