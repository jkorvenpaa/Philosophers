/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:18:52 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/05 12:04:43 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc
# include <unistd.h> //usleep
# include <string.h> //memset
# include <pthread.h>  //threads
# include <sys/time.h> //gettimeofday
# include <limits.h>
# include <stdbool.h>
# include <stdatomic.h>

typedef struct s_philo
{
	int				nbr;
	bool			even;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		id;
	atomic_long		last_supper;
	atomic_int		eat_count;
	struct s_dinner	*dinner;
}	t_philo;

typedef struct s_dinner
{
	long			party_count;
	long			start_time;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			must_eat;
	atomic_bool		stop;
	pthread_mutex_t	*printlock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_dinner;

//parsing
bool		validate_args(int argc, char **argv);
long		mini_atol(const char *nptr);
t_dinner	*init_dinner(char **argv);
void		clean_all(t_dinner *dinner, int count);

//threads
int			start_dinner(t_dinner *dinner, t_philo *philo);
void		*start_routine(void *arg);

//utils
void		*single_philo(t_philo *philo);
long		get_time(void);
void		assign_forks(t_dinner *dinner);
void		print_message(t_philo *philo, char *message);
void		pick_fork(pthread_mutex_t *fork, t_philo *philo);

//monitor
void		monitor(t_dinner *dinner);
bool		philo_alive(t_dinner *dinner, t_philo *philo);
bool		meals_done(t_dinner *dinner);

#endif