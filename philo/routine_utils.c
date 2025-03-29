/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:00:05 by mbatty            #+#    #+#             */
/*   Updated: 2024/12/03 09:28:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	try_taking_fork(t_philo *philo)
{
	if (check_death(philo) == 0)
		return (0);
	if (philo->philo_id % 2)
	{
		take_fork(philo, 2);
		take_fork(philo, 1);
	}
	else
	{
		take_fork(philo, 1);
		take_fork(philo, 2);
	}
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (check_death(philo) == 0)
		return (0);
	print_message(philo, "is sleeping");
	mssleep(philo->params->time_ts, philo);
	return (1);
}

void	take_fork(t_philo *philo, int pos)
{
	if (pos == 1)
		pthread_mutex_lock(&(*philo).left_fork->mutex);
	else if (pos == 2)
		pthread_mutex_lock(&(*philo).right_fork->mutex);
	print_message(philo, "has taken a fork");
}

void	set_philo_full(t_philo *philo, int value)
{
	pthread_mutex_lock(&(*philo).full_mutex);
	philo->full_status = value;
	pthread_mutex_unlock(&(*philo).full_mutex);
}

void	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&(*philo).dead_mutex);
	philo->dead_status = 0;
	pthread_mutex_unlock(&(*philo).dead_mutex);
}
