/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:27:22 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/02 16:38:07 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_philo *philo)
{
	t_philo	*temp;

	while (philo)
	{
		pthread_mutex_destroy(&philo->right_fork->fork);
		pthread_mutex_destroy(&philo->is_full_mutex);
		pthread_mutex_destroy(&philo->is_dead_mutex);
		pthread_mutex_destroy(&philo->last_meal_mutex);
		temp = philo;
		philo = philo->next_philo;
		free(temp->right_fork);
		free(temp);
	}
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
