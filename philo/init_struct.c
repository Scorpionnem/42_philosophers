/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:30:58 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 17:15:33 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(&fork->mutex, NULL) != 0)
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}

int	init_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->last_eaten_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->last_eaten_mutex);
		return (0);
	}
	if (pthread_mutex_init(&philo->full_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->last_eaten_mutex);
		pthread_mutex_destroy(&philo->dead_mutex);
		return (0);
	}
	return (1);
}

t_philo	*new_philo(t_params *params, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (!init_mutexes(philo))
	{
		free(philo);
		return (NULL);
	}
	philo->right_fork = init_fork();
	if (!philo->right_fork)
	{
		pthread_mutex_destroy(&philo->last_eaten_mutex);
		pthread_mutex_destroy(&philo->dead_mutex);
		pthread_mutex_destroy(&philo->full_mutex);
		free(philo);
		return (NULL);
	}
	init_philo_vars(params, philo, id);
	return (philo);
}

int	init_ints(char **av, t_params *params)
{
	params->philos = ft_atoll(av[1]);
	params->time_td = ft_atoll(av[2]);
	params->time_te = ft_atoll(av[3]);
	params->time_ts = ft_atoll(av[4]);
	if (is_invalid(params->time_td, params->time_te, params->time_ts) == 0
		|| params->philos <= 0 || params->philos > 2147483647)
		return (0);
	params->full_philos = 0;
	params->eat_amount = -1;
	return (1);
}

int	init_params(int ac, char **av, t_params *params)
{
	if (parse_params(ac, av) == 0)
		return (0);
	params->active = 1;
	if (pthread_mutex_init(&params->active_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&params->writing, NULL) != 0)
	{
		pthread_mutex_destroy(&params->active_mutex);
		return (0);
	}
	params->start_time = get_current_time();
	if (!init_ints(av, params))
		return (0);
	if (ac == 6)
		params->eat_amount = (int)ft_atoll(av[5]);
	return (1);
}
