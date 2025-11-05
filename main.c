/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:12:11 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/05 11:41:29 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	clean_all(t_dinner *dinner, int count)
{
	pthread_mutex_destroy(dinner->statelock);
	pthread_mutex_destroy(dinner->printlock);
	free(dinner->statelock);
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

int	main(int argc, char **argv)
{
	t_dinner	*dinner;

	if (!validate_args(argc, argv))
		return (1);
	dinner = init_dinner(argv);
	if (!dinner)
		return (1);
	start_dinner(dinner, dinner->philo);
	clean_all(dinner, dinner->party_count - 1);
	return (0);
}
