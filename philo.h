/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:18:52 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/01 16:00:01 by jkorvenp         ###   ########.fr       */
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
# include <limits.h> ////////////////////////////////////////////////////
# include <stdbool.h>
# include <stdatomic.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}	t_state;

typedef struct s_philo
{
	int				nbr; //placement of philo, 1->party_count
	bool			even; //  even or odd philo nbr
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		id;
	t_state			state;
	atomic_long		last_supper;
	int				eat_count;
	struct s_dinner		*dinner;
}	t_philo;

typedef struct s_dinner
{
	long			party_count; //number of forks/philos
	long			start_time;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			must_eat;
	pthread_mutex_t	*statelock;
	pthread_mutex_t	*printlock;
	pthread_mutex_t	*forks;
	t_philo	*philo;
}	t_dinner;

bool	validate_args(int argc, char **argv);
t_dinner	*init_dinner(char **argv);
int		start_dinner(t_dinner *dinner, t_philo *philo);
void	clean_all(t_dinner *dinner, int count);
long	get_time(void);
void	assign_forks(t_dinner *dinner);
void	print_message(t_philo *philo, char *message);
void	pick_fork(pthread_mutex_t *fork, t_philo *philo);
bool	anybody_dead(t_dinner *dinner);
bool	philo_alive(t_philo *philo);
bool	meals_done(t_dinner *dinner);

#endif