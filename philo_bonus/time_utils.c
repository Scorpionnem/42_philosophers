/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:28:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/31 10:23:17 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mssleep(int time, t_philo *philo)
{
	long long int	start;
	int				i;

	(void)philo;
	i = 0;
	start = get_current_time();
	while (get_current_time() - start <= time)
	{
		usleep(10);
		if (!philo->is_running)
			return ;
	}
}

long long int	get_current_time(void)
{
	struct timeval	time;
	long int		currenttime;

	gettimeofday(&time, NULL);
	currenttime = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	return (currenttime);
}
