/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:58:45 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/03 10:34:53 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atou(const char *nptr)
{
	long	n;

	n = 0;
	if (!*nptr)
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (n > (INT_MAX / 10))
			return (0);
		n = (n * 10) + (*nptr - '0');
		nptr++;
	}
	return (n);
}

static int	valid_argument(int argc, char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		while (argv[j][i] == ' ' || (argv[j][i] >= 9 && argv[j][i] <= 13))
			i++;
		if (argv[j][i] < '0' || argv[j][i] > '9')
			return (1);
		while (argv[j][i] >= '0' && argv[j][i] <= '9')
			i++;
		if (argv[j][i])
			return (1);
		j++;
	}
	return (0);
}

static void	value_to_var(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atou(argv[1]);
	data->time_to_die = ft_atou(argv[2]);
	data->time_to_eat = ft_atou(argv[3]);
	data->time_to_sleep = ft_atou(argv[4]);
	data->stop_simulation = 0;
	if (argc == 6)
		data->eat_count_max = ft_atou(argv[5]);
	else
		data->eat_count_max = 0;
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	if (valid_argument(argc, argv))
	{
		printf("Error: Ivalid arguments");
		return (1);
	}
	value_to_var(argc, argv, data);
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
	{
		printf("Error: All parameters must be greater than one.");
		return (1);
	}
	return (0);
}

