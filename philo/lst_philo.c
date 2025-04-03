/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:26:26 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/02 12:26:28 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_size(t_philo *philo)
{
	int	count;

	count = 0;
	while (philo != NULL)
	{
		count++;
		philo = philo->next_philo;
	}
	return (count);
}

t_philo	*last_philo(t_philo *philo)
{
	int	count;

	count = philo_size(philo);
	while (count > 1)
	{
		philo = philo->next_philo;
		count--;
	}
	return (philo);
}

void	add_philo_back(t_philo **head, t_philo *philo)
{
	if (!head || !philo)
		return ;
	if (*head)
	{
		last_philo(*head)->next_philo = philo;
	}
	else
		*head = philo;
}
