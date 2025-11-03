/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:11:20 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/03 18:01:57 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct	timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000L + current.tv_usec / 1000L);
}

void	print_message(t_philo *philo, char *message)
{
	long	time;
	
	pthread_mutex_lock(philo->dinner->printlock);
	time = get_time() - philo->dinner->start_time;
	if (philo->dinner->stop == false)
		printf("%ld %d %s\n", time, philo->nbr, message);
	pthread_mutex_unlock(philo->dinner->printlock);
		
}

void	pick_fork(pthread_mutex_t *fork, t_philo *philo)
{
	long	time;
	
	pthread_mutex_lock(fork);
	time = get_time() - philo->dinner->start_time;
	if (philo->dinner->stop == false)
		print_message(philo, "has taken a fork");
}

bool	philo_alive(t_dinner *dinner, t_philo *philo)
{
	if ((get_time() - philo->last_supper) > dinner->die_time)
	{
		dinner->stop = true;
		pthread_mutex_lock(dinner->printlock);
		printf("%ld %d died\n", get_time() - dinner->start_time, philo->nbr);
		pthread_mutex_unlock(dinner->printlock);
		return (false);
	}
	return (true);
		
}
bool	meals_done(t_dinner *dinner)
{
	int i;

	
	i = 0;
	while (i < dinner->party_count)
	{
		if (dinner->philo[i].eat_count < dinner->must_eat)
		{
			return(false);
		}
		i++;
	}
	dinner->stop = true;
	pthread_mutex_lock(dinner->printlock);
	printf("all philos had %ld meals\n", dinner->must_eat);
	pthread_mutex_unlock(dinner->printlock);
	return (true);
	
}
/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

