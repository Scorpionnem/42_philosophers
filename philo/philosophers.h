/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:47:53 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 17:16:38 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				valid;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_params
{
	pthread_mutex_t	writing;
	pthread_mutex_t	active_mutex;
	int				active;
	int				philos;
	long long int	start_time;
	int				full_philos;
	int				eat_amount;
	long long int	time_td;
	long long int	time_ts;
	long long int	time_te;
}	t_params;

typedef struct s_philo
{
	int						philo_id;
	struct s_philo			*next_philo;
	pthread_t				thread;
	pthread_mutex_t			dead_mutex;
	int						dead_status;
	pthread_mutex_t			full_mutex;
	int						full_status;
	t_fork					*left_fork;
	t_fork					*right_fork;
	int						food_eaten;
	pthread_mutex_t			last_eaten_mutex;
	long long int			last_eaten;
	t_params				*params;
	int						is_valid;
}	t_philo;

t_philo					*new_philo(t_params *params, int id);
int						philo_size(t_philo *philo);
t_philo					*last_philo(t_philo *philo);
void					add_philo_back(t_philo **head, t_philo *philo);

int						init_params(int ac, char **av, t_params *params);
int						ft_isdigitstr(char *str);
long long int			ft_atoll(const char *nptr);
long long int			get_current_time(void);
void					take_fork(t_philo *philo, int pos);
void					print_message(t_philo *philo, char *str);
int						check_death(t_philo *philo);
void					set_philo_full(t_philo *philo, int value);
int						check_full(t_philo *philo);
void					*ft_error(char *str);
int						start_routine(t_philo *philo);
void					mssleep(int time, t_philo *philo);
int						check_active_routine(t_params *params);
int						try_taking_fork(t_philo *philo);
int						philo_sleep(t_philo *philo);
void					kill_philo(t_philo *philo);
void					free_all(t_philo *philo);
void					init_philo_vars(t_params *params,
							t_philo *philo, int id);
int						is_invalid(long long int td,
							long long int te, long long int ts);
int						parse_params(int ac, char **av);

#endif