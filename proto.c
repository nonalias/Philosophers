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
	long dtime = time.tv_sec * 1000L + time.tv_usec / 1000L;
	return (dtime - philo->info->process_start);
}


void	print_message(void *arg_philo, char *message)
{
	t_philo	*philo;

	philo = (t_philo *)arg_philo;
	pthread_mutex_lock(&philo->info->m_mutex);
	ft_putnbr_fd(get_time(philo), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putnbr_fd(philo->index, 1);
	ft_putstr_fd(message, 1);
	pthread_mutex_unlock(&philo->info->m_mutex);
}

void	eating(void *arg_philo)
{
	t_philo	*philo;

	philo = (t_philo *)arg_philo;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	philo->info->summary_eat_count++;
	print_message(philo, " is eating\n");
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*running(void *arg_philo)
{
	t_philo *philo;

	philo = (t_philo *)arg_philo;
	printf("index : %d\n", philo->index);
	//printf("tte : %d\n", philo->info->time_to_eat);
	if (philo->index % 2 == 0)
		usleep(philo->info->time_to_eat * 1000);
	while (1)
	{
		eating(philo);
		print_message(philo, " is sleeping\n");
		usleep(philo->info->time_to_sleep * 1000);
		print_message(philo, " is thinking\n");
	}
	//printf("philo->index : %d\n", philo->index);
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
	//show_all(&a);
}
