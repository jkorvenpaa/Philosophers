/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:11:20 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/29 15:03:39 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_dinner *dinner, int count)
{
	pthread_mutex_destroy(dinner->printlock);
	free(dinner->printlock);
	while (count >= 0)
	{
		pthread_mutex_destroy(&dinner->forks[count]);
		count--;
	}
	free(dinner->forks);
	free(dinner->philo);
	free(dinner);
}

long	get_time(void)
{
	struct	timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000L + current.tv_usec / 1000L);
}

void	print_message(t_dinner *dinner, char *message)
{
	pthread_mutex_lock(dinner->printlock);
	printf("%s\n", message);
	pthread_mutex_unlock(dinner->printlock);
		
}

void	pick_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	printf("timestamp_in_ms %d has taken a fork\n", philo->nbr);
	//pthread_mutex_unlock(fork);

}
/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

