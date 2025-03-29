/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:58:22 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 13:24:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*set_philos(t_params *params)
{
	int		i;
	t_philo	*philos;
	t_philo	*newborn;

	i = 1;
	philos = NULL;
	while (i <= params->philos)
	{
		newborn = new_philo(params, i);
		if (!newborn)
		{
			free_all(philos);
			return (NULL);
		}
		add_philo_back(&philos, newborn);
		i++;
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

int	check_active_routine(t_params *params)
{
	int	value;

	value = 0;
	pthread_mutex_lock(&(*params).active_mutex);
	if (params->active == 1)
		value = 1;
	pthread_mutex_unlock(&(*params).active_mutex);
	return (value);
}

void	kill_routine(t_params *params)
{
	pthread_mutex_lock(&(*params).active_mutex);
	params->active = 0;
	pthread_mutex_unlock(&(*params).active_mutex);
}

void	check_endof_routine(t_philo *philo, t_params *params)
{
	t_philo	*first;

	first = philo;
	while (check_active_routine(params) == 1)
	{
		philo = first;
		while (philo)
		{
			if (check_death(philo) == 0)
			{
				print_message(philo, "died");
				kill_routine(params);
				break ;
			}
			if (check_full(philo) == 1)
			{
				set_philo_full(philo, 2);
				params->full_philos++;
			}
			philo = philo->next_philo;
			usleep(10);
		}
		if (params->full_philos == params->philos)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_params	params;
	t_philo		*philo;
	t_philo		*first;

	if (ac > 6 || ac < 5)
		return (!!ft_error("Error\nInvalid arguments\n"));
	if (!init_params(ac, av, &params))
		return (!!ft_error("Error\nInvalid arguments\n"));
	philo = set_philos(&params);
	if (!philo)
	{
		pthread_mutex_destroy(&params.active_mutex);
		pthread_mutex_destroy(&params.writing);
		return (!!ft_error("Error\nError when creating philos\n"));
	}
	if (start_routine(philo) == 0)
		return (!!ft_error("Error\nError when creating threads\n"));
	check_endof_routine(philo, &params);
	first = philo;
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next_philo;
	}
	free_all(first);
}
