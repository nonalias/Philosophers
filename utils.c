/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:35:27 by taehkim           #+#    #+#             */
/*   Updated: 2021/02/19 15:35:28 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

void	ft_putnbr_fd(int n, int fd)
{
	long	temp;

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
