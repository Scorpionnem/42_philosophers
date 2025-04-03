/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:15:07 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 10:44:57 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	is_sim_active(t_philo *philo)
{
	t_bool	res;

	pthread_mutex_lock(&philo->params->active_mutex);
	res = philo->params->active;
	pthread_mutex_unlock(&philo->params->active_mutex);
	return (res);
}

t_bool	is_philo_alive(t_philo *philo)
{
	t_bool	res;

	res = true;
	pthread_mutex_lock(&philo->is_dead_mutex);
	if (get_current_time() - getlastmeal(philo) >= philo->params->time_td)
	{
		philo->is_dead = true;
		res = false;
	}
	pthread_mutex_unlock(&philo->is_dead_mutex);
	return (res);
}

t_bool	is_philo_full(t_philo *philo)
{
	t_bool	res;

	res = false;
	pthread_mutex_lock(&philo->meals_mutex);
	if (philo->params->eat_amount > 0
		&& philo->meals >= philo->params->eat_amount)
		res = true;
	pthread_mutex_unlock(&philo->meals_mutex);
	return (res);
}
