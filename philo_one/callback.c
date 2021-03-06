/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:34:36 by taehkim           #+#    #+#             */
/*   Updated: 2021/02/20 09:17:12 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	eating(void *arg_philo)
{
	t_philo	*philo;

	philo = (t_philo *)arg_philo;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, " has take a fork\n");
	philo->eat_count++;
	philo->last_eat = get_time(philo);
	print_message(philo, " is eating\n");
	my_usleep(philo, philo->info->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	give_time_interval(t_philo *philo)
{
	if (philo->index % 2 == 0)
		my_usleep(philo, philo->info->time_to_eat);
	if (philo->info->number_of_philosophers % 2 == 1 &&
			philo->index == philo->info->number_of_philosophers)
		my_usleep(philo, philo->info->time_to_eat * 2);
}

void	*running(void *arg_philo)
{
	t_philo		*philo;
	pthread_t	die_check;

	philo = (t_philo *)arg_philo;
	pthread_create(&die_check, NULL, die_monitoring, arg_philo);
	give_time_interval(philo);
	while (philo->info->status == P_STATUS_NONE &&
			philo->eat_count <
			philo->info->number_of_times_each_philosopher_must_eat)
	{
		eating(philo);
		if (philo->eat_count ==
				philo->info->number_of_times_each_philosopher_must_eat)
		{
			philo->status = P_STATUS_EAT_COUNT_FULL;
			break ;
		}
		print_message(philo, " is sleeping\n");
		my_usleep(philo, philo->info->time_to_sleep);
		print_message(philo, " is thinking\n");
	}
	return (void *)NULL;
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
