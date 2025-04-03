/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:30:05 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 10:18:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(const char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->params->writing);
	if (is_sim_active(philo))
	{
		printf("%lld %d ",
			get_current_time() - philo->params->start_time, philo->id);
		printf("%s", str);
		printf("\n");
	}
	pthread_mutex_unlock(&philo->params->writing);
}

void	take_fork(t_philo *philo, t_forkdir dir)
{
	if (dir == left)
		pthread_mutex_lock(&philo->left_fork->fork);
	if (dir == right)
		pthread_mutex_lock(&philo->right_fork->fork);
	print_message(MSG_FORK, philo);
}

void	release_fork(t_philo *philo, t_forkdir dir)
{
	if (dir == left)
		pthread_mutex_unlock(&philo->left_fork->fork);
	if (dir == right)
		pthread_mutex_unlock(&philo->right_fork->fork);
}

void	eat(t_philo *philo)
{
	print_message(MSG_EAT, philo);
	if (mssleep(philo->params->time_te, philo))
	{
		addmeal(philo);
		setlastmeal(philo);
	}
	release_fork(philo, left);
	release_fork(philo, right);
}

void	p_sleep(t_philo *philo)
{
	print_message(MSG_SLEEP, philo);
	mssleep(philo->params->time_ts, philo);
}
