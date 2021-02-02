#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define P_STATUS_NONE 0
#define P_STATUS_EAT 1
#define P_STATUS_SLEEP 2
#define P_STATUS_THINK 3
#define P_STATUS_DEAD 4

#define RELEASE 0
#define GREB 1

#define NORMAL 0
#define DIED 1
#define PHILO_INTERVAL 100

typedef struct	s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				status;
	int				process_start;
}				t_info;

typedef struct	s_philo
{
	pthread_t		tid;
	struct timeval	tv;
	t_info			*info;
	int				index;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int				status;
	int				eat_count;
}				t_philo;

int		ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		wr_error(char *error_msg)
{
	write(1, &"Error: ", 7);
	write(1, error_msg, ft_strlen(error_msg));
	write(1, &"\n", 1);
	return (1);
}

int		ft_atoi(char *str)
{
	int		opt;
	int		result;
	int		i;

	opt = 1;
	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-')
	{
		i++;
		opt = -1;
	}
	result = 0;
	while (str[i])
	{
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	return (result * opt);
}

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

int		philo_init(t_philo **philo, t_info *info)
{
	int		i;

	*philo = malloc(sizeof(t_philo) * info->number_of_philosophers);
	(*philo)->info = info;
	if (!*philo)
		return (1);
	i = 0;
	while (i < info->number_of_philosophers)
	{
		(*philo)[i].index = i + 1;
		pthread_mutex_init(&(*philo)[i].left_fork, NULL);
		pthread_mutex_init(&(*philo)[i].right_fork, NULL);
		(*philo)[i].status = P_STATUS_NONE;
		(*philo)[i].eat_count = 0;
		i++;
	}
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
	info->status = NORMAL;
	info->process_start = gettimeofday(&time, NULL);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
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

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;

	while (*str)
	{
		write(fd, &*str, 1);
		str++;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	long long	temp;

	temp = n;
	if (temp < 0)
	{
		write(fd, &"-"[0], 1);
		temp = -temp;
	}
	if (temp > 9)
		ft_putnbr_fd(temp / 10, fd);
	write(fd, &"0123456789"[temp % 10], 1);
}


void	print_message(t_philo *philo, char *message)
{
	ft_putnbr_fd(philo->info->process_start, 1);
	ft_putstr_fd(" ms ", 1);
}

void	*running(void *arg_philo)
{
	t_philo *philo;

	philo = (t_philo *)arg_philo;
	/*
	if (philo->index % 2 == 0)
		usleep(philo->info->time_to_eat);
	while (philo->info->status != DIED)
	{
		eating(philo);
		print_message(philo, " is sleeping\n");
		usleep(philo->info->time_to_sleep);
		print_message(philo, " is thinking\n");
	}
	*/
	printf("philo->index : %d\n", philo->index);
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
		//pthread_mutex_lock(&mt);
		gettimeofday(&philo[i].tv, NULL);
		//printf("philo[i].tv.tv_usec : %d\n", philo[i].tv.tv_usec);
		pthread_create(&(philo[i].tid), NULL, running, &(philo[i]));
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
