/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:35:22 by taehkim           #+#    #+#             */
/*   Updated: 2021/02/19 16:21:08 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	time_to_msec(struct timeval time)
{
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

long	get_time(t_philo *philo)
{
	struct timeval	time;
	long			dtime;

	gettimeofday(&time, NULL);
	dtime = time_to_msec(time);
	return (dtime - philo->info->process_start);
}

void	my_usleep(t_philo *philo, long time)
{
	long	target;

	target = time + 1000 * get_time(philo);
	while (target > 1000 * get_time(philo))
		usleep(100);
}
