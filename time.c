/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:35:22 by taehkim           #+#    #+#             */
/*   Updated: 2021/02/19 15:35:24 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
