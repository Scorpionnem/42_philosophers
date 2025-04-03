/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:42:11 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 11:06:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	addmeal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_mutex);
}

void	setlastmeal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

long long	getlastmeal(t_philo *philo)
{
	long long	res;

	pthread_mutex_lock(&philo->last_meal_mutex);
	res = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (res);
}

static int	init_mutexes_philo_2(t_philo *philo)
{
	if (pthread_mutex_init(&philo->right_fork->fork, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->last_meal_mutex);
		pthread_mutex_destroy(&philo->is_dead_mutex);
		pthread_mutex_destroy(&philo->is_full_mutex);
		return (0);
	}
	if (pthread_mutex_init(&philo->meals_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->last_meal_mutex);
		pthread_mutex_destroy(&philo->is_dead_mutex);
		pthread_mutex_destroy(&philo->is_full_mutex);
		pthread_mutex_destroy(&philo->right_fork->fork);
		return (0);
	}
	return (1);
}

int	init_mutexes_philo(t_philo *philo)
{
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->is_dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->last_meal_mutex);
		return (0);
	}
	if (pthread_mutex_init(&philo->is_full_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->last_meal_mutex);
		pthread_mutex_destroy(&philo->is_dead_mutex);
		return (0);
	}
	return (init_mutexes_philo_2(philo));
}
