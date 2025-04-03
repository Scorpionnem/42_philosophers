/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:01:07 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 11:00:52 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	start_philos(t_params *params)
{
	t_philo	*philo;

	philo = params->philos;
	pthread_mutex_lock(&params->wait_start);
	while (philo)
	{
		if (pthread_create(&philo->thread, NULL, philo_routine, philo) != 0)
			return (0);
		philo = philo->next_philo;
	}
	pthread_mutex_unlock(&params->wait_start);
	return (1);
}

void	close_params(t_params *params)
{
	t_philo	*tmp;

	tmp = params->philos;
	while (tmp)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next_philo;
	}
	free_all(params->philos);
}

static void	stop_sim(t_params *params, t_philo *cur_philo, t_reason reason)
{
	pthread_mutex_lock(&params->writing);
	if (reason == death)
		printf("%lld %d died\n",
			get_current_time() - cur_philo->params->start_time, cur_philo->id);
	if (reason == feast)
		printf("%lld everyone ate enough\n",
			get_current_time() - cur_philo->params->start_time);
	if (reason == error)
		printf(EXEC_ERROR);
	pthread_mutex_lock(&params->active_mutex);
	params->active = false;
	pthread_mutex_unlock(&params->active_mutex);
}

static void	monitor(t_params *params)
{
	t_philo	*tmp;
	int		full_philos;

	tmp = params->philos;
	full_philos = 0;
	while (tmp)
	{
		if (!is_philo_alive(tmp))
			return (stop_sim(params, tmp, death));
		if (is_philo_full(tmp))
			full_philos++;
		if (full_philos == params->philos_count)
			return (stop_sim(params, tmp, feast));
		tmp = tmp->next_philo;
		if (!tmp)
		{
			full_philos = 0;
			tmp = params->philos;
		}
	}
}

int	main(int ac, char **av)
{
	t_params	params;

	if (ac > 6 || ac < 5)
		return (!ft_error(INVALID_ARGSC));
	if (!init_params(ac, av, &params))
		return (!ft_error(INVALID_ARGS));
	params.philos = create_philos(&params);
	if (!params.philos)
		return (!ft_error(PHIL_ERROR));
	if (!start_philos(&params))
		stop_sim(&params, NULL, error);
	else
	{
		mssleep(params.time_td / 2, NULL);
		monitor(&params);
	}
	pthread_mutex_unlock(&params.writing);
	close_params(&params);
}
