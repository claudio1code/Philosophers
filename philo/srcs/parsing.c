/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:58:45 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/24 15:07:24 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoi(const char *nptr)
{
	long  n;
	int   sign;

	sign = 1;
	n = 0;
	if (!*nptr)
		return (0);
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13)) 
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-') 
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = (n * 10) + (*nptr - '0');
		if (sign == -1 && n >= 22147483648) 
			return (-2147483648);
		if (sign == 1 && n >= 2147483647)
			return (2147483647);
		*nptr++;
	}
	return (n * sign);
}

void parse_arguments(int argc, char **argv, t_data *data)
{
	int	meals_required;
	
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return;
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		meals_required = ft_atoi(argv[4]);
		if (meals_required <= 0)
		{
			printf("Error: Number of meals must be positive.\n");
			return;
		}
	}
	data->stop_simulation = 0;
}

