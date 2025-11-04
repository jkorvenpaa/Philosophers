/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:57:53 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/04 12:32:25 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_dinner *dinner)
{
	int	i;

	while (get_time() < dinner->start_time)
		usleep(500);
	while (1)
	{
		i = 0;
		while(i < dinner->party_count)
		{
			if (!philo_alive(dinner, &dinner->philo[i]))
				return ;
			i++;
		}
		if (dinner->must_eat != 0)
		{
			if (meals_done(dinner))
				return;
		}
		usleep (500);
	}
}
bool	philo_alive(t_dinner *dinner, t_philo *philo)
{
	long	time;

	time = get_time();
	if ((time - philo->last_supper) > dinner->die_time)
	{
		dinner->stop = true;
		pthread_mutex_lock(dinner->printlock);
		printf("%ld %d died\n", time - dinner->start_time, philo->nbr);
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
			return (false);
		i++;
	}
	dinner->stop = true;
	pthread_mutex_lock(dinner->printlock);
	printf("all philos had %ld meals\n", dinner->must_eat);
	pthread_mutex_unlock(dinner->printlock);
	return (true);	
}