/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:45:35 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/30 16:49:12 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_cycle(t_philo *philo, t_dinner *dinner)
{
	philo->state = EATING;
	print_message(philo, "eating");
	philo->last_supper = get_time();
	philo->eat_count++;
	while (dinner->eat_time > (get_time() - dinner->start_time))
		usleep(100);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->state = SLEEPING;
	print_message(philo, "sleeping");
	while (philo->dinner->sleep_time > (get_time() - dinner->start_time))
		usleep(100);
}

void	*start_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo*) arg;

	while (get_time() < philo->dinner->start_time)
		usleep(100);
	philo->last_supper = philo->dinner->start_time;
	//int i = 0;
	if (philo->dinner->party_count == 1)
		return (NULL);
	while (1)
	{
		if (anybody_dead(philo->dinner) || meals_done(philo->dinner))
			return (NULL);
		if (philo_alive(philo))
		{
			philo->state = THINKING;
			print_message(philo, "thinking");
		}
		else
			return (NULL);
		if(philo->even)
		{
			usleep (200);
			pick_fork(philo->r_fork, philo);
			pick_fork(philo->l_fork, philo);
			if (philo_alive(philo) && anybody_dead(philo->dinner) == false)
				philo_cycle(philo, philo->dinner);
		}
		else // odd philo
		{
			pick_fork(philo->l_fork, philo);
			pick_fork(philo->r_fork, philo);
			if (philo_alive(philo) && anybody_dead(philo->dinner) == false)
				philo_cycle(philo, philo->dinner);
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
