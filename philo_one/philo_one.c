/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:35:12 by taehkim           #+#    #+#             */
/*   Updated: 2021/02/19 15:35:18 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_message(void *arg_philo, char *message)
{
	t_philo	*philo;

	philo = (t_philo *)arg_philo;
	if (philo->info->status == P_STATUS_NONE)
	{
		pthread_mutex_lock(&philo->info->m.message);
		ft_putnbr_fd(get_time(philo), 1);
		ft_putstr_fd("ms idx ", 1);
		ft_putnbr_fd(philo->index, 1);
		ft_putstr_fd(message, 1);
		pthread_mutex_unlock(&philo->info->m.message);
	}
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
		usleep(PHILO_INTERVAL);
		i++;
	}
	i = 0;
	while (i < info.number_of_philosophers)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}
