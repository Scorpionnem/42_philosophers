/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:25:26 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 13:41:23 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_params(int ac, char **av)
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

static int	is_invalid(long long int td, long long int te, long long int ts)
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

static int	init_ints(char **av, t_params *params)
{
	params->philos = ft_atoll(av[1]);
	params->time_td = ft_atoll(av[2]);
	params->time_te = ft_atoll(av[3]);
	params->time_ts = ft_atoll(av[4]);
	if (is_invalid(params->time_td, params->time_te, params->time_ts) == 0
		|| params->philos <= 0 || params->philos > 2147483647)
		return (0);
	params->eat_amount = -1;
	return (1);
}

int	init_params(int ac, char **av, t_params *params)
{
	if (parse_params(ac, av) == 0)
		return (0);
	params->active = 1;
	params->start_time = get_current_time();
	if (!init_ints(av, params))
		return (0);
	if (ac == 6)
		params->eat_amount = (int)ft_atoll(av[5]);
	return (1);
}
