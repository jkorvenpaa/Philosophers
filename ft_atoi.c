/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:35:42 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/22 17:32:24 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*converts the initial portion of the string pointed to by nptr to int.*/

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			return (-1);
			//sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (sign == 1 && res > ((INT_MAX - (nptr[i] - '0')) / 10))
			return (-2); //(INT_MAX);
		/*if (sign == -1 && res > ((-(long)INT_MIN - (nptr[i] - '0')) / 10))
			return (INT_MIN);*/
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)(res * sign));
}
