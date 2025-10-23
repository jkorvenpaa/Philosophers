/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:18:52 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/23 18:28:46 by jkorvenp         ###   ########.fr       */
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
	int				number; //placement of philo, 0->party_count
	//int			forks;
	int				eat_count;
	t_state			state;
	struct s_philo	*next;
}	t_philo;

typedef struct s_dinner
{
	int		party_count; //number of forks/philos
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat;
	t_philo	**philo;
}	t_dinner;

int		ft_atoi(const char *nptr);
bool	validate_args(int argc, char **argv);

#endif