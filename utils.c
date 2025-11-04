/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:11:20 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/04 12:35:02 by jkorvenp         ###   ########.fr       */
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
	pthread_mutex_lock(fork);
	if (philo->dinner->stop == false)
		print_message(philo, "has taken a fork");
}

void	*single_philo(t_philo *philo)
{
	print_message(philo, "is thinking");
	pick_fork(philo->l_fork, philo);
	pthread_mutex_unlock(philo->l_fork);
	while (philo->dinner->stop == false)
		usleep (500);
	return (NULL);

}

