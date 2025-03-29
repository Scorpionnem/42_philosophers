/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:47:53 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/29 19:27:12 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <signal.h>

typedef struct s_params
{
	pthread_t		waitphilos;
	sem_t			*forks;
	sem_t			*is_running;
	sem_t			*print;
	sem_t			*killsem;
	int				active;
	int				philos;
	int				eat_amount;
	long long int	start_time;
	long long int	time_td;
	long long int	time_ts;
	long long int	time_te;
	int				id;
	int				*pid;
	int				kill;
}	t_params;

typedef struct s_philo
{
	int				is_running;
	long long int	last_eat;
	int				times_eaten;
	pthread_t		checkhimselfthread;
	t_params		*params;
}	t_philo;

# define FORK_SEM "/forks_semaphore"
# define PRINT_SEM "/print_semaphore"
# define RUN_SEM "/run_semaphore"
# define KILL_SEM "/kill_semaphore"

//params.c
int				init_params(int ac, char **av, t_params *params);

//utils.c
void			*ft_error(char *str);
long long int	ft_atoll(const char *nptr);
int				ft_isdigitstr(char *str);

//time_utils.c
long long int	get_current_time(void);
void			mssleep(int time, t_philo *philo);

//actions.c
void			p_sleep(t_params *params, t_philo *philo);
void			eat(t_params *params, t_philo *philo);
void			take_fork(t_params *params, t_philo *philo);
void			print_message(const char *str,
					t_params *params, t_philo *philo);

//philos.c
int				philo_routine(t_params *params, int id);

#endif