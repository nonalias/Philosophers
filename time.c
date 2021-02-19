#include "philo_one.h"

long 	get_time(t_philo *philo)
{
	struct timeval	time;
	long			dtime;

	gettimeofday(&time, NULL);
	dtime = T_TO_MS(time.tv_sec, time.tv_usec);
	return (dtime - philo->info->process_start);
}

void	my_usleep(t_philo *philo, long time)
{
	long	target;

	target = time + 1000 * get_time(philo);
	while (target > 1000 * get_time(philo))
		usleep(100);
}
