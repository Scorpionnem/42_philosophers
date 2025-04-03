/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:29:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 11:05:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		take_fork(philo, left);
		take_fork(philo, right);
	}
	else
	{
		take_fork(philo, right);
		take_fork(philo, left);
	}
}

static void	*alone(t_philo *philo)
{
	take_fork(philo, right);
	release_fork(philo, right);
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_mutex_lock(&philo->params->wait_start);
	pthread_mutex_unlock(&philo->params->wait_start);
	if (philo->id % 2)
		usleep(50);
	if (philo->params->philos_count == 1)
		return (alone(philo));
	while (is_sim_active(philo))
	{
		pick_forks(philo);
		eat(philo);
		p_sleep(philo);
		print_message(MSG_THINK, philo);
	}
	return (NULL);
}
