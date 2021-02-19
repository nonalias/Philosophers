/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:34:59 by taehkim           #+#    #+#             */
/*   Updated: 2021/02/19 21:18:20 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
int		fork_init(t_philo **philo, int i, char *temp, char *itemp)
{
	//itemp = ft_itoa(i);
	if (i == 0)
	{
		temp = ft_strjoin("leftfork", itemp);
		sem_unlink(temp);
		(*philo)[i].left_fork = sem_open(temp, O_CREAT, S_IRWXU, 1);
		free(temp);
		if (!((*philo)[i].left_fork))
			return (1);
	}
	else
		(*philo)[i].left_fork = (*philo)[i - 1].right_fork;
	if (i == (*philo)[i].info->number_of_philosophers - 1)
		(*philo)[i].right_fork = (*philo)[0].left_fork;
	else
	{
		temp = ft_strjoin("rightfork", itemp);
		sem_unlink(temp);
		(*philo)[i].right_fork = sem_open(temp, O_CREAT, S_IRWXU, 1);
		free(temp);
		if (!((*philo)[i].right_fork))
			return (1);
	}
	free(itemp);
	return (0);
}
	*/

int		philo_init(t_philo **philo, t_info *info)
{
	int		i;

	*philo = malloc(sizeof(t_philo) * info->number_of_philosophers);
	sem_unlink("my_forks");
	info->forks = sem_open("my_forks", O_CREAT, S_IRWXU, info->number_of_philosophers);
	if (!*philo)
		return (1);
	i = 0;
	while (i < info->number_of_philosophers)
	{
		(*philo)[i].info = info;
		(*philo)[i].index = i + 1;
		//if (fork_init(philo, i, NULL, NULL))
			//return (1);
		(*philo)[i].eat_count = 0;
		(*philo)[i].info->eat_count[i] = &(*philo)[i].eat_count;
		(*philo)[i].last_eat = 0;
		(*philo)[i].status = P_STATUS_NONE;
		i++;
	}
	return (0);
}

void	semaphore_init(t_info *info)
{
	sem_unlink("p_message");
	sem_unlink("p_check_die");
	sem_unlink("p_check_full");
	info->sem.message = sem_open("p_message", O_CREAT, S_IRWXU, 1);
	info->sem.check_die = sem_open("p_check_die", O_CREAT, S_IRWXU, 1);
	info->sem.check_full = sem_open("p_check_full", O_CREAT, S_IRWXU, 1);
}

int		init(t_info *info, int argc, char **argv)
{
	struct timeval	time;

	if (valid_check(argv))
		return (1);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]) * 1000;
	info->time_to_sleep = ft_atoi(argv[4]) * 1000;
	info->status = P_STATUS_NONE;
	info->summary_eat_count = 0;
	info->eat_count = malloc(sizeof(int **) * info->number_of_philosophers);
	semaphore_init(info);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = 987654321;
	gettimeofday(&time, NULL);
	info->process_start = time_to_msec(time);
	return (0);
}
