/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:05:36 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 12:56:44 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_error(char *str)
{
	printf("%s", str);
	return (NULL);
}

void	free_all(t_philo *philo)
{
	t_philo	*temp;

	while (philo)
	{
		pthread_mutex_destroy(&(*philo).right_fork->mutex);
		pthread_mutex_destroy(&(*philo).full_mutex);
		pthread_mutex_destroy(&(*philo).dead_mutex);
		pthread_mutex_destroy(&(*philo).last_eaten_mutex);
		free(philo->right_fork);
		temp = philo;
		philo = philo->next_philo;
		free(temp);
	}
}
