/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:29:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 12:33:34 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_checkhimself(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (1)
	{
		sem_wait(philo->check_auto);
		if (get_current_time() - philo->last_eat >= philo->params->time_td)
		{
			sem_wait(philo->params->print);
			printf("%lld %d died\n",
				get_current_time() - philo->params->start_time,
				philo->params->id + 1);
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
		sem_post(philo->check_auto);
	}
	return (NULL);
}

static int	start_threads(t_philo *philo)
{
	philo->check_auto = open_sem(CHECK_AUTO, 1);
	if (!philo->check_auto)
		return (0);
	if (pthread_create(&philo->checkhimselfthread,
			NULL, philo_checkhimself, philo) != 0)
	{
		sem_close(philo->check_auto);
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
	sem_wait(params->wait_start);
	sem_post(params->wait_start);
	if (params->id % 2)
		mssleep(1, &philo);
	while (philo.is_running)
	{
		take_fork(params, &philo);
		take_fork(params, &philo);
		eat(params, &philo);
		p_sleep(params, &philo);
		if (!philo.is_running)
			break ;
		print_message(MSG_THINK, params, &philo);
	}
	pthread_join(philo.checkhimselfthread, NULL);
	sem_close(philo.check_auto);
	sem_close(params->forks);
	sem_close(params->print);
	sem_close(params->is_running);
	sem_close(params->touch_kill);
	exit(0);
}
