#include "philo_one.h"

int		valid_check(char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}



/*
void	show_all(t_all *a)
{
	printf("a->i : %d\n", a->i);
	printf("a->n_philo : %d\n", a->n_philo);
	printf("a->ttd : %d\n", a->ttd);
	printf("a->tte : %d\n", a->tte);
	printf("a->tts : %d\n", a->tts);
	printf("a->n_times_must_eat : %d\n", a->n_times_must_eat);
}
*/

long 	get_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	long dtime = T_TO_MS(time.tv_sec, time.tv_usec);
	//long dtime = time.tv_sec * 1000L + time.tv_usec / 1000L;
	return (dtime - philo->info->process_start);
}

void	my_usleep(t_philo *philo, long time)
{
	long	target;

	target = time + 1000 * get_time(philo);
		//printf("target : %ld, get_time(philo) : %ld\n", target, get_time(philo));
	while (target > 1000 * get_time(philo))
	{
		//printf("target : %ld, get_time(philo) : %ld\n", target, get_time(philo));
		usleep(100);
	}
}


void	print_message(void *arg_philo, char *message)
{
	t_philo	*philo;

	philo = (t_philo *)arg_philo;
	if (philo->info->status == P_STATUS_NONE)
	{
		pthread_mutex_lock(&philo->info->m.message);
		ft_putnbr_fd(get_time(philo), 1);
		ft_putstr_fd(" ms ", 1);
		ft_putnbr_fd(philo->index, 1);
		ft_putstr_fd(message, 1);
		pthread_mutex_unlock(&philo->info->m.message);
	}
}

void	*die_monitoring(void *arg_philo)
{
	t_philo *philo;

	philo = (t_philo *)arg_philo;
	while (philo->info->status == P_STATUS_NONE)
	{
		if (philo->status == P_STATUS_EAT_COUNT_FULL)
			return (void *)NULL;
		if (get_time(philo) - philo->last_eat > philo->info->time_to_die)
		{
			pthread_mutex_lock(&philo->info->m.check_die);
			print_message(philo, " died\n");
			philo->info->status = P_STATUS_DEAD;
			pthread_mutex_unlock(&philo->info->m.check_die);
		}
	}
	return (void *)NULL;
}

void	eating(void *arg_philo)
{
	t_philo	*philo;

	philo = (t_philo *)arg_philo;
	//if (check_priority(philo))
		//usleep(philo->info->time_to_eat);
	pthread_mutex_lock(philo->left_fork);
	//print_message(philo, " has take a left fork\n");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, " has take a fork\n");
	philo->eat_count++;
	philo->last_eat = get_time(philo);
	print_message(philo, " is eating\n");
	my_usleep(philo, philo->info->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
/*

void	*full_monitoring(void *arg_philo)
{
	t_philo	*philo;

	philo = (t_philo *)arg_philo;
	if (philo->info->number_of_times_each_philosopher_must_eat == -1)
		return (void *)NULL;
	while (philo->info->status == P_STATUS_NONE)
	{
		if (philo->eat_count == 
	}
}
*/

void	*running(void *arg_philo)
{
	t_philo *philo;
	pthread_t	die_check;

	philo = (t_philo *)arg_philo;
	pthread_create(&die_check, NULL, die_monitoring, arg_philo);
	//pthread_create(&full_check, NULL, full_monitoring, arg_philo);
	//printf("index : %d\n", philo->index);
	//printf("tte : %d\n", philo->info->time_to_eat);
	if (philo->index % 2 == 0)
		my_usleep(philo, philo->info->time_to_eat);
	//if (philo->info->number_of_philosophers % 2 == 0)
	//{
		//if (philo->index % 2 == 0)
		//	my_usleep(philo, philo->info->time_to_eat);
	//}
	if (philo->info->number_of_philosophers % 2 == 1 &&
			philo->index == philo->info->number_of_philosophers)
		my_usleep(philo, philo->info->time_to_eat * 2);
	while (philo->info->status == P_STATUS_NONE &&
			philo->eat_count < philo->info->number_of_times_each_philosopher_must_eat)
	{
		eating(philo);
		if (philo->eat_count == philo->info->number_of_times_each_philosopher_must_eat)
		{
			philo->status = P_STATUS_EAT_COUNT_FULL;
			break;
		}
		print_message(philo, " is sleeping\n");
		my_usleep(philo, philo->info->time_to_sleep);
		print_message(philo, " is thinking\n");
	}
	//printf("philo->index : %d\n", philo->index);
	return (void *)NULL;
}

int		main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;
	int		i;

	if (argc < 5 || argc > 6)
		return (wr_error("Wrong number of arguments"));
	if (init(&info, argc, argv))
		return (wr_error("Wrong Argument"));
	if (philo_init(&philo, &info))
		return (wr_error("philo init failed"));
	i = 0;
	while (i < info.number_of_philosophers)
	{
		pthread_create(&philo[i].tid, NULL, running, &(philo[i]));
		//pthread_mutex_unlock(&mt);
		usleep(PHILO_INTERVAL);
		i++;
	}
	i = 0;
	while (i < info.number_of_philosophers)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	//:while(1);
	//show_all(&a);
}
