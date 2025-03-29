/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:05:51 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 17:13:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_pasta(t_philo *philo)
{
	if (check_death(philo) == 0)
	{
		pthread_mutex_unlock(&(*philo).right_fork->mutex);
		pthread_mutex_unlock(&(*philo).left_fork->mutex);
		return (0);
	}
	print_message(philo, "is eating");
	mssleep(philo->params->time_te, philo);
	pthread_mutex_unlock(&(*philo).right_fork->mutex);
	pthread_mutex_unlock(&(*philo).left_fork->mutex);
	pthread_mutex_lock(&(*philo).last_eaten_mutex);
	philo->last_eaten = get_current_time();
	pthread_mutex_unlock(&(*philo).last_eaten_mutex);
	philo->food_eaten++;
	if (philo->food_eaten == philo->params->eat_amount)
	{
		set_philo_full(philo, 1);
		return (0);
	}
	return (1);
}

int	check_death(t_philo *philo)
{
	int	state;

	state = 1;
	pthread_mutex_lock(&(*philo).dead_mutex);
	pthread_mutex_lock(&(*philo).params->active_mutex);
	pthread_mutex_lock(&(*philo).last_eaten_mutex);
	if (philo->params->active == 0)
		state = 0;
	if ((get_current_time() - philo->last_eaten) >= philo->params->time_td)
		state = 0;
	pthread_mutex_unlock(&(*philo).last_eaten_mutex);
	if (state == 0)
		philo->dead_status = 0;
	pthread_mutex_unlock(&(*philo).params->active_mutex);
	pthread_mutex_unlock(&(*philo).dead_mutex);
	return (state);
}

int	check_full(t_philo *philo)
{
	int	value;

	value = 1;
	pthread_mutex_lock(&(*philo).full_mutex);
	if (philo->full_status == 0 || philo->full_status == 2)
		value = 0;
	pthread_mutex_unlock(&(*philo).full_mutex);
	return (value);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_id % 2 == 0)
		usleep(10);
	while (1)
	{
		if (philo->params->philos == 1)
		{
			take_fork(philo, 2);
			pthread_mutex_unlock(&(*philo).right_fork->mutex);
			break ;
		}
		if (try_taking_fork(philo) == 0)
			break ;
		if (eat_pasta(philo) == 0)
			break ;
		if (philo_sleep(philo) == 0)
			break ;
		print_message(philo, "is thinking");
		usleep(10);
	}
	kill_philo(philo);
	pthread_exit(0);
}

int	start_routine(t_philo *philo)
{
	while (philo)
	{
		if (pthread_create(&philo->thread, NULL, routine, philo) != 0)
			return (0);
		philo = philo->next_philo;
	}
	return (1);
}
