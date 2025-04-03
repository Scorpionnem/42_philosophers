/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:01:07 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 11:46:50 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*wait_philos(void *ptr)
{
	t_params	*params;
	int			i;

	i = 0;
	params = ptr;
	sem_wait(params->is_running);
	sem_wait(params->touch_kill);
	while (i < params->philos)
	{
		if (params->kill && params->pid[i] > 0)
			kill(params->pid[i], SIGKILL);
		i++;
	}
	sem_post(params->touch_kill);
	return (NULL);
}

static int	launch_routines(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->philos)
		params->pid[i] = 0;
	i = -1;
	while (++i < params->philos)
	{
		params->pid[i] = fork();
		if (params->pid[i] == -1)
		{
			i = -1;
			while (++i < params->philos)
				if (params->pid[i] > 0)
					kill(params->pid[i], SIGKILL);
			return (0);
		}
		if (!params->pid[i])
		{
			free(params->pid);
			philo_routine(params, i);
		}
	}
	return (1);
}

static int	start_philos(t_params *params)
{
	int	i;

	i = -1;
	params->kill = 1;
	params->pid = malloc(params->philos * sizeof(int));
	if (!params->pid)
		return (0);
	if (!launch_routines(params))
		return (0);
	if (pthread_create(&params->waitphilos, NULL, wait_philos, params) != 0)
		return (0);
	while (++i < params->philos)
		waitpid(params->pid[i], 0, 0);
	sem_wait(params->touch_kill);
	params->kill = 0;
	sem_post(params->touch_kill);
	sem_post(params->is_running);
	return (1);
}

static int	open_all_sems(t_params *params)
{
	params->forks = open_sem(FORK_SEM, params->philos);
	if (!params->forks)
		return (!!ft_error(SEM_FAIL_FORKS));
	params->print = open_sem(PRINT_SEM, 1);
	if (!params->print)
	{
		sem_close(params->forks);
		return (!!ft_error(SEM_FAIL_PRINT));
	}
	params->is_running = open_sem(RUN_SEM, 0);
	if (!params->is_running)
	{
		sem_close(params->forks);
		sem_close(params->is_running);
		return (!!ft_error(SEM_FAIL_DEATH));
	}
	params->touch_kill = open_sem(KILL_SEM, 1);
	if (!params->touch_kill)
	{
		sem_close(params->forks);
		sem_close(params->is_running);
		sem_close(params->touch_kill);
		return (!!ft_error(SEM_FAIL_KILL));
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_params	params;

	if (ac > 6 || ac < 5)
		return (!ft_error(INVALID_ARGSC));
	if (!init_params(ac, av, &params))
		return (!ft_error(INVALID_ARGS));
	if (!open_all_sems(&params))
		return (1);
	if (!start_philos(&params))
		printf(EXEC_ERROR);
	close_params(&params);
}
