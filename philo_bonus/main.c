/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:01:07 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 19:45:20 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t	*open_sem(const char *sem_name, int startval)
{
	sem_t	*res;

	sem_unlink(sem_name);
	res = sem_open(sem_name, O_CREAT, 0644, startval);
	if (res == SEM_FAILED)
		return (NULL);
	return (res);
}

void	*wait_philos(void *ptr)
{
	t_params	*params;
	int			i;

	params = ptr;
	sem_wait(params->is_running);
	i = 0;
	sem_wait(params->killsem);
	while (i < params->philos)
	{
		if (params->kill)
			kill(params->pid[i], SIGKILL);
		i++;
	}
	sem_post(params->killsem);
	return (NULL);
}

int	start_philos(t_params *params)
{
	int	i;

	i = -1;
	params->kill = 1;
	params->pid = malloc(params->philos * sizeof(int));
	while (++i < params->philos)
	{
		params->pid[i] = fork();
		if (!params->pid[i])
		{
			free(params->pid);
			philo_routine(params, i);
		}
	}
	i = -1;
	if (pthread_create(&params->waitphilos, NULL, wait_philos, params) != 0)
		return (0);
	while (++i < params->philos)
		waitpid(params->pid[i], 0, 0);
	sem_wait(params->killsem);
	params->kill = 0;
	sem_post(params->killsem);
	sem_post(params->is_running);
	free(params->pid);
	return (1);
}

int	init_sems(t_params *params)
{
	params->forks = open_sem(FORK_SEM, params->philos);
	if (!params->forks)
		return (!!ft_error("Error\nFailed to open semaphore"));
	params->print = open_sem(PRINT_SEM, 1);
	if (!params->print)
	{
		sem_close(params->forks);
		return (!!ft_error("Error\nFailed to open semaphore"));
	}
	params->is_running = open_sem(RUN_SEM, 0);
	if (!params->is_running)
	{
		sem_close(params->forks);
		sem_close(params->print);
		return (!!ft_error("Error\nFailed to open semaphore"));
	}
	params->killsem = open_sem(KILL_SEM, 1);
	if (!params->killsem)
	{
		sem_close(params->forks);
		sem_close(params->print);
		sem_close(params->is_running);
		return (!!ft_error("Error\nFailed to open semaphore"));
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_params	params;

	if (ac > 6 || ac < 5)
		return (!!ft_error("Error\nInvalid arguments\n"));
	if (!init_params(ac, av, &params))
		return (!!ft_error("Error\nInvalid arguments\n"));
	if (!init_sems(&params))
		return (1);
	start_philos(&params);
	pthread_join(params.waitphilos, NULL);
	sem_close(params.forks);
	sem_close(params.print);
	sem_close(params.is_running);
	sem_close(params.killsem);
}
