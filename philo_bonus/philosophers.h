/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:47:53 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 11:44:19 by mbatty           ###   ########.fr       */
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
	sem_t			*touch_kill;
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
	sem_t			*check_auto;
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
# define CHECK_AUTO "/check_auto_semaphore"

# define INVALID_ARGSC "Error\nInvalid amount of arguments\n"
# define INVALID_ARGS "Error\nInvalid arguments\n"
# define SEM_FAIL_FORKS "Error\nFailed to open forks semaphore\n"
# define SEM_FAIL_PRINT "Error\nFailed to open print semaphore\n"
# define SEM_FAIL_DEATH "Error\nFailed to open death check semaphore\n"
# define SEM_FAIL_KILL "Error\nFailed to open kill check semaphore\n"
# define EXEC_ERROR "Error\nAn error occured when executing the program\n"

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"
# define MSG_FINISH "\033[0;92mfinished eating\033[0m"

//params.c
int				init_params(int ac, char **av, t_params *params);

//utils.c
void			*ft_error(const char *str);
long long int	ft_atoll(const char *nptr);
int				ft_isdigitstr(const char *str);
sem_t			*open_sem(const char *sem_name, int startval);
void			close_params(t_params *params);

//time_utils.c
long long int	get_current_time(void);
int				mssleep(int time, t_philo *philo);

//actions.c
void			p_sleep(t_params *params, t_philo *philo);
void			eat(t_params *params, t_philo *philo);
void			take_fork(t_params *params, t_philo *philo);
void			print_message(const char *str,
					t_params *params, t_philo *philo);

//philos.c
int				philo_routine(t_params *params, int id);

#endif