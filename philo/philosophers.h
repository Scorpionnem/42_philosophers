/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:47:53 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/03 11:05:34 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_forkdir
{
	left,
	right
}	t_forkdir;

typedef enum e_reason
{
	death,
	feast,
	error
}	t_reason;

typedef struct s_fork
{
	t_mutex	fork;
}	t_fork;

typedef struct s_philo
{
	struct s_philo			*next_philo;
	pthread_t				thread;
	int						id;
	t_mutex					is_dead_mutex;
	t_bool					is_dead;
	t_mutex					is_full_mutex;
	t_bool					is_full;
	t_fork					*left_fork;
	t_fork					*right_fork;
	int						meals;
	t_mutex					meals_mutex;
	t_mutex					last_meal_mutex;
	long long int			last_meal;
	struct s_params			*params;
}	t_philo;

typedef struct s_params
{
	t_philo			*philos;
	t_mutex			writing;
	t_mutex			wait_start;
	t_mutex			active_mutex;
	t_bool			active;
	int				philos_count;
	int				eat_amount;
	long long int	start_time;
	long long int	time_td;
	long long int	time_ts;
	long long int	time_te;
	long long int	time_smallest;
}	t_params;

# define INVALID_ARGSC "Error\nInvalid amount of arguments\n"
# define INVALID_ARGS "Error\nInvalid arguments\n"
# define EXEC_ERROR "Error\nAn error occured when executing the program\n"
# define PHIL_ERROR "Error\nAn error occured when creating the philos\n"

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"
# define MSG_FINISH "\033[0;92mfinished eating\033[0m"

//main.c
void			close_params(t_params *params);

//mutex.c
void			addmeal(t_philo *philo);
void			setlastmeal(t_philo *philo);
long long		getlastmeal(t_philo *philo);
int				init_mutexes_philo(t_philo *philo);

//params.c
int				init_params(int ac, char **av, t_params *params);

//utils.c
void			*ft_error(const char *str);
long long int	ft_atoll(const char *nptr);
int				ft_isdigitstr(const char *str);
void			free_all(t_philo *philo);

//time_utils.c
long long int	get_current_time(void);
int				mssleep(int time, t_philo *philo);

//actions.c
void			print_message(const char *str, t_philo *philo);
void			take_fork(t_philo *philo, t_forkdir dir);
void			eat(t_philo *philo);
void			p_sleep(t_philo *philo);
void			release_fork(t_philo *philo, t_forkdir dir);

//philos.c
void			*philo_routine(void *ptr);
t_bool			is_sim_active(t_philo *philo);
t_bool			is_philo_alive(t_philo *philo);
t_bool			is_philo_full(t_philo *philo);

t_philo			*create_philos(t_params *params);
t_philo			*new_philo(t_params *params, int id);
void			init_philo_vars(t_params *params, t_philo *philo, int id);

//lst_philo.c
int				philo_size(t_philo *philo);
t_philo			*last_philo(t_philo *philo);
void			add_philo_back(t_philo **head, t_philo *philo);

#endif