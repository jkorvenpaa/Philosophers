/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:18:52 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/25 16:30:17 by jkorvenp         ###   ########.fr       */
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

typedef enum e_state
{
	START,
	EATING,
	THINKING,
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
}	t_philo;

typedef struct s_dinner
{
	int				party_count; //number of forks/philos
	long			start_time;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	pthread_mutex_t	*printlock;
	pthread_mutex_t	*forks;
	t_philo	*philo;
}	t_dinner;

int		ft_atoi(const char *nptr);
bool	validate_args(int argc, char **argv);
void	start_dinner(t_dinner *dinner, t_philo *philo);

#endif