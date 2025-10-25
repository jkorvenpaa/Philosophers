/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:12:11 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/25 16:29:57 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

#include "philo.h"

void	free_philos(t_dinner *dinner, t_philo **philo, int i)
{
	while (i >= 0)
	{
		free(philo[i]);
		i--;
	}
	free(philo);
	free(dinner);
}

t_philo	**init_philos(t_dinner *dinner)
{
	t_philo	**philo;
	int		i;

	philo = malloc(sizeof(t_philo *) * dinner->party_count);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < dinner->party_count)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			free_philos(dinner, philo, i);
			return (NULL);
		}
		memset(philo[i], 0, sizeof(t_philo));
		philo[i]->nbr = i+1;
		if ((i+1) % 2 == 0)
			philo[i]->even = true;
		i++;
	}
	return (philo);
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
	dinner->philo = init_philos(dinner);
	if (dinner->philo == NULL) //|| die_time < eat_time + sleep_time)
	{
		free (dinner);
		return (NULL);
	}
	return (dinner);
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;

	memset(dinner, 0, sizeof(t_dinner));
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