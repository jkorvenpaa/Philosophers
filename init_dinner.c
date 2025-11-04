/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:26:11 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/04 15:20:36 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->party_count)
	{
		dinner->philo[i].r_fork = &dinner->forks[i];
		if (i == 0)
			dinner->philo[i].l_fork = &dinner->forks[dinner->party_count - 1];
		else
			dinner->philo[i].l_fork = &dinner->forks[i - 1];
		i++;
	}
}

bool	init_philos(t_dinner *dinner)
{
	int		i;

	dinner->philo = malloc(sizeof(t_philo) * dinner->party_count);
	if (!dinner->philo)
	{
		clean_all(dinner, dinner->party_count - 1);
		return (false);
	}
	i = 0;
	while (i < dinner->party_count)
	{
		memset(&dinner->philo[i], 0, sizeof(t_philo));
		dinner->philo[i].nbr = i + 1;
		if ((i + 1) % 2 == 0)
			dinner->philo[i].even = true;
		dinner->philo[i].dinner = dinner;
		i++;
	}
	assign_forks(dinner);
	return (true);
}

bool	init_mutex(t_dinner *dinner)
{
	dinner->statelock = malloc(sizeof(pthread_mutex_t));
	if (!dinner->statelock)
		return (false);
	if (pthread_mutex_init(dinner->statelock, NULL) != 0)
	{
		free(dinner->statelock);
		return (false);
	}
	dinner->printlock = malloc(sizeof(pthread_mutex_t));
	if (!dinner->printlock)
	{
		pthread_mutex_destroy(dinner->statelock);
		free(dinner->statelock);
		return (false);
	}
	if (pthread_mutex_init(dinner->printlock, NULL) != 0)
	{
		pthread_mutex_destroy(dinner->statelock);
		free(dinner->statelock);
		free(dinner->printlock);
		return (false);
	}
	return (true);
}

bool	init_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->party_count);
	if (!dinner->forks)
	{
		pthread_mutex_destroy(dinner->printlock);
		pthread_mutex_destroy(dinner->statelock);
		free(dinner->statelock);
		free(dinner->printlock);
		free(dinner);
		return (false);
	}
	while (i < dinner->party_count)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
		{
			clean_all(dinner, i);
			return (false);
		}
		i++;
	}
	return (true);
}

t_dinner	*init_dinner(char **argv)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (NULL);
	dinner->party_count = mini_atol(argv[1]);
	dinner->die_time = mini_atol(argv[2]);
	dinner->eat_time = mini_atol(argv[3]);
	dinner->sleep_time = mini_atol(argv[4]);
	if (argv[5])
		dinner->must_eat = mini_atol(argv[5]);
	else
		dinner->must_eat = 0;
	dinner->stop = false;
	dinner->philo = NULL;
	if (!init_mutex(dinner))
	{
		free(dinner);
		return (NULL);
	}
	if (!init_forks(dinner))
		return (NULL);
	if (!init_philos(dinner))
		return (NULL);
	return (dinner);
}
