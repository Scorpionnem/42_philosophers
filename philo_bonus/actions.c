/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:30:05 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 12:33:40 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(const char *str, t_params *params, t_philo *philo)
{
	sem_wait(params->print);
	usleep(10);
	if (philo->is_running)
	{
		printf("%lld %d ",
			get_current_time() - params->start_time, params->id + 1);
		printf("%s", str);
		printf("\n");
	}
	sem_post(params->print);
}

void	take_fork(t_params *params, t_philo *philo)
{
	sem_wait(params->forks);
	print_message(MSG_FORK, params, philo);
}

static void	release_fork(t_params *params)
{
	sem_post(params->forks);
}

void	eat(t_params *params, t_philo *philo)
{
	print_message(MSG_EAT, params, philo);
	sem_wait(philo->check_auto);
	if (mssleep(params->time_te, philo))
	{
		// if ()
		// 	printf("I AM SUPOSED TO DIE\n");
		philo->times_eaten++;
		philo->last_eat = get_current_time();
	}
	sem_post(philo->check_auto);
	release_fork(params);
	release_fork(params);
}

void	p_sleep(t_params *params, t_philo *philo)
{
	print_message(MSG_SLEEP, params, philo);
	mssleep(params->time_ts, philo);
}
