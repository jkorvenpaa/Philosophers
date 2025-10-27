/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:12:11 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/27 12:19:03 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

#include "philo.h"


bool	init_philos(t_dinner *dinner)
{
	int		i;

	dinner->philo = malloc(sizeof(t_philo) * dinner->party_count);
	if (!dinner->philo)
	{
		free(dinner);
		return (false);
	}
	i = 0;
	while (i < dinner->party_count)
	{
		memset(&dinner->philo[i], 0, sizeof(t_philo));
		dinner->philo[i].nbr = i+1;
		if ((i+1) % 2 == 0)
			dinner->philo[i].even = true;
		i++;
	}
	return (true);
}
void	assign_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->party_count)
	{
		dinner->philo[i].r_fork = &dinner->forks[i];
		if (i < 0)
			dinner->philo[i].l_fork = &dinner->forks[i];
		else
			dinner->philo[i].l_fork = &dinner->forks[dinner->party_count-1];
		i++;
	}

}

bool	init_forks(t_dinner *dinner)
{
	int		i;

	i = 0;
	pthread_mutex_init(dinner->printlock, NULL) != 0;
		return (false);
	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->party_count);
	if (!dinner->forks)
	{
		pthread_mutex_destroy(dinner->printlock);
		return (false);
	}
	while (i < dinner->party_count)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(dinner->printlock);
			while (i >= 0)
			{
				pthread_mutex_destroy(&dinner->forks[i]);
				i--;
			}
			return (false);
		}
		i++;
	}
	assign_forks(dinner);
	return (true);
}

t_dinner	*init_dinner(char **argv)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (NULL);
	dinner->party_count = ft_atoi(argv[1]);
	dinner->die_time = ft_atoi(argv[2]);
	dinner->eat_time = ft_atoi(argv[3]);
	dinner->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		dinner->must_eat = ft_atoi(argv[5]);
	else
		dinner->must_eat = 0;
	if (!init_philos(dinner))//|| die_time < eat_time + sleep_time)
		return (NULL);
	if(!init_forks(dinner))
	{
		free(dinner->philo);
		free(dinner);
		return (NULL);
	}
	return (dinner);
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;

	if (!validate_args(argc, argv))
		return (1);
	dinner = init_dinner(argv);
	if (!dinner)
		return (1);
	start_dinner(dinner, dinner->philo);
	free_philos(dinner, dinner->philo, dinner->party_count-1);
	return (0);
}

	/*
	argv[0] = philo
	argv[1] = number_of_philosophers (=nuumber of forks)
	argv[2] = time_to_die (1 ms = usleep(1000) (us))
	argv[3] = time_to_eat (1 ms = usleep(1000))
	argv[4] = time_to_sleep (1 ms = usleep(1000))
	[number_of_times_each_philosopher_must_eat]
}*/