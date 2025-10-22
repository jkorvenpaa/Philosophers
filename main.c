/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:12:11 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/22 17:56:24 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

# include "philo.h"

void free_philos(t_philo **philo, int i)
{
	while (i >= 0)
	{
		free(philo[i]);
		i--;
	}
	free(philo);
}

t_philo	**init_philos(t_dinner *dinner)
{
	t_philo	**philo;
	int	i;

	philo = malloc(sizeof(t_philo*)*dinner->party_count);
	i = 0;
	while (i < dinner->party_count)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			free_philos(philo, i);
			return(NULL);
		}
		philo[i]->number = i;
		//philo->forks = 0;
		philo[i]->eat_count = 0;
		philo[i]->state = 0;
		philo[i]->next = NULL;
		i++;
	}
	printf("hey philos done");
	return (philo);
}


t_dinner	*init_dinner(char ** argv)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (NULL);
	dinner->party_count = ft_atoi(argv[1]);
	printf("%d\n", dinner->party_count);
	dinner->die_time = ft_atoi(argv[2]);
	printf("%d\n", dinner->die_time);
	dinner->eat_time = ft_atoi(argv[3]);
	printf("%d\n", dinner->eat_time);
	dinner->sleep_time = ft_atoi(argv[4]);
	printf("%d\n", dinner->sleep_time);
	dinner->must_eat = ft_atoi(argv[5]);
	printf("%d\n", dinner->must_eat);
	dinner->philo = init_philos(dinner);

	if (dinner->philo == NULL)
	{
		free(dinner);
		return (NULL);
	}
	//printf("%d\n", dinner->philo[dinner->party_count-1]->number);

	return (dinner);

}


int	main(int argc, char **argv)
{
	t_dinner	*dinner;

	
	if (argc != 5 && argc != 6)
		return (1);
	dinner = init_dinner(argv);
	if (!dinner)
		return (1);
	free_philos(dinner->philo, dinner->party_count-1);
	free(dinner);
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