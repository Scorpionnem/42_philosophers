/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:34:19 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 17:14:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mssleep(int time, t_philo *philo)
{
	int				i;
	long long int	start;

	(void)philo;
	i = 0;
	start = get_current_time();
	while (get_current_time() - start <= time)
	{
		usleep(10);
		if (check_death(philo) == 0)
			return ;
	}
}

void	print_message(t_philo *philo, char *str)
{
	long int	time;

	time = get_current_time() - philo->params->start_time;
	pthread_mutex_lock(&(*philo).params->writing);
	if (check_active_routine(philo->params) == 1)
		printf("%lu %d %s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(&(*philo).params->writing);
}

long long int	get_current_time(void)
{
	struct timeval	time;
	long int		currenttime;

	gettimeofday(&time, NULL);
	currenttime = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	return (currenttime);
}

long long int	ft_atoll(const char *nptr)
{
	int				i;
	int				minus_count;
	long long int	nb;

	nb = 0;
	minus_count = 0;
	i = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus_count++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	if (minus_count == 1)
		return (nb * -1);
	return (nb);
}

int	ft_isdigitstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}
