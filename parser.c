/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:55:01 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/11/02 15:29:48 by jkorvenp         ###   ########.fr       */
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

bool	init_philos(t_dinner *dinner)
{
	int		i;

	dinner->philo = malloc(sizeof(t_philo) * dinner->party_count);
	if (!dinner->philo)
	{
		free(dinner);
		return (false);
	}
	i = 0;
	while (i < dinner->party_count)
	{
		memset(&dinner->philo[i], 0, sizeof(t_philo));
		dinner->philo[i].nbr = i+1;
		if ((i+1) % 2 == 0)
			dinner->philo[i].even = true;
		dinner->philo[i].dinner = dinner;
		i++;
	}
	return (true);
}
void	assign_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->party_count)
	{
		dinner->philo[i].r_fork = &dinner->forks[i];
		if (i == 0)
			dinner->philo[i].l_fork = &dinner->forks[dinner->party_count-1];	
		else
			dinner->philo[i].l_fork = &dinner->forks[i-1];
			
		i++;
	}

}
bool	init_mutex(t_dinner *dinner)
{
	dinner->statelock = malloc(sizeof(pthread_mutex_t));
	if (!dinner->statelock)
		return(false);
	if (pthread_mutex_init(dinner->statelock, NULL) != 0)
	{
		free(dinner->statelock);
		return(false);
	}
	dinner->printlock = malloc(sizeof(pthread_mutex_t));
	if (!dinner->printlock)
	{
		pthread_mutex_destroy(dinner->statelock);
		free(dinner->statelock);
		return(false);
	}
	if (pthread_mutex_init(dinner->printlock, NULL) != 0)
	{
		pthread_mutex_destroy(dinner->statelock);
		free(dinner->statelock);
		free(dinner->printlock);
		return(false);
	}
	return (true);
}

bool	init_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->party_count);
	if (!dinner->forks)
	{
		pthread_mutex_destroy(dinner->printlock);
		pthread_mutex_destroy(dinner->statelock);
		free(dinner->philo);
		free(dinner->statelock);
		free(dinner->printlock);
		free(dinner);
		return (false);
	}
	while (i < dinner->party_count)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
		{
			clean_all(dinner, i);
			return (false);
		}
		i++;
	}
	assign_forks(dinner);
	return (true);
}


t_dinner	*init_dinner(char **argv)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (NULL);
	dinner->party_count = mini_atol(argv[1]);
	dinner->die_time = mini_atol(argv[2]);
	dinner->eat_time = mini_atol(argv[3]);
	dinner->sleep_time = mini_atol(argv[4]);
	if (argv[5])
		dinner->must_eat = mini_atol(argv[5]);
	else
		dinner->must_eat = 0;
	dinner->stop = false;
	if (!init_philos(dinner))//|| die_time < eat_time + sleep_time)
		return (NULL);
	if(!init_mutex(dinner))
	{
		free(dinner->philo);
		free(dinner);
		return (NULL);
	}
	if(!init_forks(dinner))
		return (NULL);
	return (dinner);
}
