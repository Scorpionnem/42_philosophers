/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:27:22 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/31 11:06:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	close_params(t_params *params)
{
	if (params->pid)
		free(params->pid);
	sem_close(params->forks);
	sem_close(params->print);
	sem_close(params->touch_kill);
	sem_close(params->is_running);
	pthread_join(params->waitphilos, NULL);
}

void	*ft_error(const char *str)
{
	printf("%s", str);
	return (NULL);
}

int	ft_isdigitstr(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

long long int	ft_atoll(const char *nptr)
{
	int				i;
	int				minus_count;
	long long int	nb;

	nb = 0;
	minus_count = 0;
	i = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus_count++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	if (minus_count == 1)
		return (nb * -1);
	return (nb);
}

sem_t	*open_sem(const char *sem_name, int startval)
{
	sem_t	*res;

	sem_unlink(sem_name);
	res = sem_open(sem_name, O_CREAT, 0644, startval);
	if (res == SEM_FAILED)
		return (NULL);
	return (res);
}
