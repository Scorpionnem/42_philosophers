/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:14:57 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 17:15:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_params(int ac, char **av)
{
	int	i;

	i = ac - 1;
	while (i > 2)
	{
		if (!ft_isdigitstr(av[i]))
			return (0);
		i--;
	}
	return (1);
}

int	is_invalid(long long int td, long long int te, long long int ts)
{
	if (td <= 0 || te <= 0 || ts <= 0)
		return (0);
	if (td > 2147483647 || td < -2147483648)
		return (0);
	if (te > 2147483647 || te < -2147483648)
		return (0);
	if (ts > 2147483647 || ts < -2147483648)
		return (0);
	return (1);
}

void	init_philo_vars(t_params *params, t_philo *philo, int id)
{
	philo->params = params;
	philo->philo_id = id;
	philo->next_philo = NULL;
	philo->food_eaten = 0;
	philo->last_eaten = params->start_time;
	philo->dead_status = 0;
	philo->full_status = 0;
	philo->left_fork = NULL;
}
