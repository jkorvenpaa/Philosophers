/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:12:11 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/17 12:30:16 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock*/

# include "philo.h"

int	main(int argc, char **argv)
{
	if (argc > 1)
		printf("%s", argv[1]);
	return (0);
}

	/*
	argv[0] = philo
	argv[1] = number_of_philosophers
	argv[2] = time_to_die
	argv[3] = time_to_eat
	argv[4] = time_to_sleep
	[number_of_times_each_philosopher_must_eat]
}*/