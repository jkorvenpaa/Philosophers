/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:55:01 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/10/25 16:11:00 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	else
		return (1);
}

static bool	numeric_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] == 32 || (arg[i] >= 9 && arg[i] <= 13)))
		i++;
	if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit == 0)
			return (false);
		i++;
	}
	return (true);
}

bool	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("invalid argument count");
		return (false);
	}
	while (argv[i])
	{
		if (!numeric_arg)
		{
			printf("numeric arguments expected\n");
			return (false);
		}
		if (ft_atoi(argv[i]) <= 0) //must eat???
		{
			printf("arguments expected: number between 1 and INTMAX\n");
			return (false);
		}
		i++;
	}
	return (true);
}
