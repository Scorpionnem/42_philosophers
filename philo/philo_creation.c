/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:14:34 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 11:05:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo_vars(t_params *params, t_philo *philo, int id)
{
	philo->params = params;
	philo->id = id;
	philo->next_philo = NULL;
	philo->meals = 0;
	philo->last_meal = params->start_time;
	philo->is_dead = 0;
	philo->is_full = 0;
	philo->left_fork = NULL;
}

t_philo	*new_philo(t_params *params, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->right_fork = malloc(sizeof(t_fork));
	if (!philo->right_fork)
	{
		free(philo);
		return (NULL);
	}
	if (!init_mutexes_philo(philo))
	{
		free(fork);
		free(philo);
		return (NULL);
	}
	init_philo_vars(params, philo, id);
	return (philo);
}

t_philo	*create_philos(t_params *params)
{
	int		i;
	t_philo	*philos;
	t_philo	*newborn;

	i = 0;
	philos = NULL;
	while (++i <= params->philos_count)
	{
		newborn = new_philo(params, i);
		if (!newborn)
		{
			free_all(philos);
			close_params(params);
			return (NULL);
		}
		add_philo_back(&philos, newborn);
	}
	newborn = philos;
	while (newborn->next_philo)
	{
		newborn->next_philo->left_fork = newborn->right_fork;
		newborn = newborn->next_philo;
	}
	philos->left_fork = last_philo(philos)->right_fork;
	return (philos);
}
