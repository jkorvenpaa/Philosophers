/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:11:20 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/28 15:57:26 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_dinner *dinner, int count)
{
	pthread_mutex_destroy(dinner->printlock);
	free(dinner->printlock);
	while (count >= 0)
	{
		pthread_mutex_destroy(&dinner->forks[count]);
		count--;
	}
	free(dinner->forks);
	free(dinner->philo);
	free(dinner);
}

long	get_time(void)
{
	struct	timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000L + current.tv_usec / 1000L);
}

