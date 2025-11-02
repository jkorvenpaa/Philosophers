/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:45:35 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/02 15:48:52 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_cycle(t_philo *philo, t_dinner *dinner)
{
	long	s_time;
	long	e_time;

	print_message(philo, "eating");
	philo->last_supper = get_time();
	e_time = get_time();
	while (dinner->eat_time > (get_time() - e_time) && (dinner->stop == false))
		usleep(100);
	philo->eat_count++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	print_message(philo, "sleeping");
	s_time = get_time();
	while (dinner->sleep_time > (get_time() - s_time) && (dinner->stop == false))
		usleep(100);
}

void	*start_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo*) arg;
	philo->last_supper = philo->dinner->start_time;
	while (get_time() < philo->dinner->start_time)
		usleep(100);
	if (philo->dinner->party_count == 1)
	{
		pick_fork(philo->l_fork, philo);
		while (philo->dinner->stop == false)
			usleep (500);
		return (NULL);
	}
	while (1)
	{
		if (philo->dinner->stop == true)
			return (NULL);
		else
			print_message(philo, "thinking");
		if(!philo->even)
		{
			usleep (200);
			pick_fork(philo->r_fork, philo);
			pick_fork(philo->l_fork, philo);
			if (philo->dinner->stop == false)
				philo_cycle(philo, philo->dinner);
		}
		else // odd philo
		{
			pick_fork(philo->l_fork, philo);
			pick_fork(philo->r_fork, philo);
			if (philo->dinner->stop == false)
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
		usleep (500);
	}
}

int	start_dinner(t_dinner *dinner, t_philo	*philo)
{
	int	i;

	i = 0;
	dinner->start_time = get_time() + 500;
	
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
