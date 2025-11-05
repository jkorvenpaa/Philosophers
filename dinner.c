/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:45:35 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/05 11:37:05 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo, t_dinner *dinner)
{
	long	s_time;

	print_message(philo, "is sleeping");
	s_time = get_time();
	while (dinner->sleep_time > (get_time() - s_time))
		usleep(500);
}

void	philo_eat(t_philo *philo, t_dinner *dinner)
{
	long	e_time;

	print_message(philo, "is eating");
	philo->last_supper = get_time();
	e_time = get_time();
	while (dinner->eat_time > (get_time() - e_time))
		usleep(500);
	philo->eat_count++;
}

void	prepare_to_eat(t_philo *philo)
{
	if ((!philo->even))
	{
		pick_fork(philo->l_fork, philo);
		pick_fork(philo->r_fork, philo);
	}
	else
	{
		pick_fork(philo->r_fork, philo);
		pick_fork(philo->l_fork, philo);
	}
	philo_eat(philo, philo->dinner);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
void	philo_think(t_philo *philo, t_dinner *dinner)
{
	long time;

	print_message(philo, "is thinking");
	time = get_time();
	if ((time + dinner->die_time) < (time + dinner->sleep_time + dinner->eat_time + 1000))
		usleep(500);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;
	long	sleepy;

	philo = (t_philo *) arg;
	philo->last_supper = philo->dinner->start_time;
	while (get_time() < philo->dinner->start_time)
		usleep(500);
	if (philo->dinner->party_count == 1)
		return (single_philo(philo));
	sleepy = (philo->dinner->eat_time / 2) * 1000;
	if (!philo->even)
		usleep(sleepy);
	while (!philo->dinner->stop)
	{
		philo_think(philo, philo->dinner);
		prepare_to_eat(philo);
		if (philo->dinner->stop)
			return (NULL);
		philo_sleep(philo, philo->dinner);
	}
	return (NULL);
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
