/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:12:11 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/28 16:06:15 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

#include "philo.h"

void	print_args (t_dinner *dinner)
{
	printf("%d\n", dinner->party_count);
	printf("%ld\n", dinner->start_time);
	printf("%d\n", dinner->die_time);
	printf("%d\n", dinner->eat_time);
	printf("%d\n", dinner->sleep_time);
	printf("%d\n", dinner->must_eat);
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
	print_args (dinner);
	clean_all(dinner, dinner->party_count-1);
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