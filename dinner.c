/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:45:35 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/01 18:02:49 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_cycle(t_philo *philo, t_dinner *dinner)
{
	long	s_time;
	long	e_time;

	//philo->state = EATING;
	print_message(philo, "eating");
	philo->last_supper = get_time();
	e_time = get_time();
	while (dinner->eat_time > (get_time() - e_time) && (philo->state!=DEAD))
		usleep(200);
	philo->eat_count++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	//philo->state = SLEEPING;
	print_message(philo, "sleeping");
	s_time = get_time();
	while (philo->dinner->sleep_time > (get_time() - s_time) && (philo->state!=DEAD))
		usleep(200);
}

void	*start_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo*) arg;

	while (get_time() < philo->dinner->start_time)
		usleep(100);
	philo->last_supper = philo->dinner->start_time;
	if (philo->dinner->party_count == 1)
	{
		pick_fork(philo->l_fork, philo);
		while (philo_alive(philo))
			usleep (100);
		return (NULL);
	}
	while (philo->state != DEAD)
	{
		if (anybody_dead(philo->dinner) || meals_done(philo->dinner))
			return (NULL);
		if (philo->state == THINKING)
		{
			//philo->state = THINKING;
			print_message(philo, "thinking");
		}
		else
			return (NULL);
		if(philo->even)
		{
			usleep (200);
			pick_fork(philo->r_fork, philo);
			pick_fork(philo->l_fork, philo);
			if (anybody_dead(philo->dinner) == false)
				philo_cycle(philo, philo->dinner);
		}
		else // odd philo
		{
			pick_fork(philo->l_fork, philo);
			pick_fork(philo->r_fork, philo);
			if (anybody_dead(philo->dinner) == false)
				philo_cycle(philo, philo->dinner);
		}
	}
	return (NULL);
}

void	monitor(t_dinner *dinner)
{
	int i = 0;

	while (get_time() < dinner->start_time)
		usleep(100);
	while (1)
	{
		while(i < dinner->party_count)
		{
			if (!philo_alive(&dinner->philo[i]))
				return ;
			i++;
		}
		i = 0;
		if (meals_done(dinner))
		{
			return;
		}
		usleep (200);
	}
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
	monitor(dinner);
	i = 0;
	while (i < dinner->party_count)
	{
		if (pthread_join(philo[i].id, NULL) != 0)
			return (2);
		i++;
	}
	
	return (0);
}
