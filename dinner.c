/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:45:35 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/05 12:04:53 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
