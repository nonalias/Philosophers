#ifndef PHILO_ONE__H

# define PHILO_ONE__H
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

# define P_STATUS_NONE 0
# define P_STATUS_DEAD 1
# define P_STATUS_EAT_COUNT_FULL 1

# define RELEASE 0
# define GREB 1

# define PHILO_INTERVAL 100

typedef struct	s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				status;
	long			process_start;
	int				summary_eat_count;
	pthread_mutex_t	m_mutex;
}				t_info;

typedef struct	s_philo
{
	pthread_t		tid;
	t_info			*info;
	int				index;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_eat;
	int				eat_count;
}				t_philo;

/*
**  utils.c
*/

int		ft_strlen(char *str);
int		wr_error(char *error_msg);
int		ft_atoi(char *str);
void	ft_putstr_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);

/*
**  init.c
*/

int		philo_init(t_philo **philo, t_info *info);
int		init(t_info *info, int argc, char **argv);


int		valid_check(char **argv);
#endif