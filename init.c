#include "philo_one.h"

int		philo_init(t_philo **philo, t_info *info)
{
	int		i;

	*philo = malloc(sizeof(t_philo) * info->number_of_philosophers);
	if (!*philo)
		return (1);
	i = 0;
	while (i < info->number_of_philosophers)
	{
        (*philo)[i].info = info;
		(*philo)[i].index = i + 1;
		if (i == 0)
			(*philo)[i].left_fork = malloc(sizeof(pthread_mutex_t));
		else
			(*philo)[i].left_fork = (*philo)[i - 1].right_fork;
		if (i == info->number_of_philosophers - 1)
			(*philo)[i].right_fork = (*philo)[0].left_fork;
		else
			(*philo)[i].right_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((*philo)[i].right_fork, NULL);
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}

int		init(t_info *info, int argc, char **argv)
{
	struct timeval	time;

	if (valid_check(argv))
		return (1);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->status = P_STATUS_NONE;
	gettimeofday(&time, NULL);
	info->process_start = time.tv_sec * 1000L + time.tv_usec / 1000L;
	info->summary_eat_count = 0;
	pthread_mutex_init(&info->m_mutex, NULL);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}