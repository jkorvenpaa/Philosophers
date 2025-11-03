/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:55:01 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/03 13:27:27 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static bool	numeric_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13)))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (arg[i] < 48 || arg[i] > 57)
			return (false);
		i++;
	}
	return (true);
}
long	mini_atol(const char *nptr)
{
	long	i;
	//long	sign;
	long long	out;

	i = 0;
	//sign = 1;
	out = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (out > INT_MAX)//(LONG_MAX - (nptr[i] - '0')) / 10)
			return (-2);
	//	if (sign == -1 && ((-1 * out) < (LONG_MIN + (nptr[i] - '0')) / 10))
	//		return (LONG_MIN);
		out = out * 10 + nptr[i] - '0';
		i++;
	}
	return ((long)(out));
}

bool	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("invalid argument count\n");
		return (false);
	}
	while (argv[i])
	{
		if (!numeric_arg(argv[i]))
		{
			printf("numeric arguments expected\n");
			return (false);
		}
		if (mini_atol(argv[i]) <= 0) //must eat???
		{
			printf("arguments expected: number between 1 and INTMAX\n");
			return (false);
		}
		i++;
	}
	return (true);
}



