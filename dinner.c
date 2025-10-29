/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:45:35 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/29 15:21:41 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_eating(t_philo *philo)
{
	philo->state = EATING;
	philo->last_supper = get_time();
	philo->eat_count = philo->eat_count++;
	while (philo->dinner->eat_time > get_time())
		usleep(100);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->state = SLEEPING;
}

void	*start_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo*) arg;

	while (get_time() < philo->dinner->start_time)
		usleep(100);
	//int i = 0;
	if (philo->dinner->party_count = 1)
		return (NULL);
	while (1)
	{
		usleep (100);
		if (philo->state == DEAD)
			break;
		if(philo->even)
		{
			pick_fork(philo->r_fork, philo);
			pick_fork(philo->l_fork, philo);
			philo_eating(philo);
		}
		else // odd philo
		{
			pick_fork(philo->l_fork, philo);
			pick_fork(philo->r_fork, philo);
			philo_eating(philo);
		}
	}
	return (NULL);
}


int	start_dinner(t_dinner *dinner, t_philo	*philo)
{
	int	i;

	i = 0;
	dinner->start_time = get_time() + 300;
	
	while (i < dinner->party_count)
	{
		if (pthread_create(&philo[i].id, NULL, start_routine, &philo[i]) != 0)
			return (1);
		i++;
	}

	i = 0;
	while (i < dinner->party_count)
	{
		if (pthread_join(philo[i].id, NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}
