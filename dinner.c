/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:45:35 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/06 11:35:03 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_dinner *dinner, t_philo	*philo)
{
	int	i;

	i = 0;
	dinner->start_time = get_time() + 500;
	while (i < dinner->party_count)
	{
		if (pthread_create(&philo[i].id, NULL, start_routine, &philo[i]) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_join(philo[i].id, NULL);
			}
			return ;
		}
		i++;
	}
	monitor(dinner);
	i = 0;
	while (i < dinner->party_count)
	{
		pthread_join(philo[i].id, NULL);
		i++;
	}
}
