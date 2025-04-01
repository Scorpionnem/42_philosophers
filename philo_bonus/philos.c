/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:29:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/31 10:58:40 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_checkhimself(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (1)
	{
		if (get_current_time() - philo->last_eat >= philo->params->time_td)
		{
			print_message(MSG_DIED, philo->params, philo);
			sem_post(philo->params->is_running);
			break ;
		}
		if (philo->times_eaten >= philo->params->eat_amount
			&& philo->params->eat_amount != -1)
		{
			print_message(MSG_FINISH, philo->params, philo);
			philo->is_running = 0;
			break ;
		}
	}
	return (NULL);
}

static int	start_threads(t_philo *philo)
{
	if (pthread_create(&philo->checkhimselfthread,
			NULL, philo_checkhimself, philo) != 0)
	{
		sem_close(philo->params->forks);
		sem_close(philo->params->print);
		sem_close(philo->params->is_running);
		sem_close(philo->params->touch_kill);
		return (0);
	}
	return (1);
}

static t_philo	init_philo(t_params *params, int id)
{
	t_philo	res;

	params->id = id;
	res.is_running = 1;
	res.params = params;
	res.last_eat = get_current_time();
	res.times_eaten = 0;
	return (res);
}

int	philo_routine(t_params *params, int id)
{
	t_philo	philo;

	philo = init_philo(params, id);
	if (!start_threads(&philo))
		exit(0);
	if (params->id % 2)
		mssleep(1, &philo);
	while (philo.is_running)
	{
		take_fork(params, &philo);
		take_fork(params, &philo);
		eat(params, &philo);
		p_sleep(params, &philo);
		print_message(MSG_THINK, params, &philo);
	}
	sem_close(params->forks);
	sem_close(params->print);
	sem_close(params->is_running);
	sem_close(params->touch_kill);
	pthread_join(philo.checkhimselfthread, NULL);
	exit(0);
}
