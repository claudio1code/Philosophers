/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:21:29 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/04 17:23:13 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_global_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL)
		|| pthread_mutex_init(&data->monitor_lock, NULL))
	{
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philosophers(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].data = data;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = get_time();
		if (pthread_mutex_init(&(*philos)[i].philo_lock, NULL))
			return (1);
		(*philos)[i].left_fork = &data->forks[i];
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	int			i;

	if (parse_arguments(argc, argv, &data))
		return (1);
	if (init_global_data(&data))
		return (1);
	if (init_philosophers(&philos, &data))
	{
		printf("Error: Falied to initialize philosophers.\n");
		free(data.forks);
		return (1);
	}
	if (start_simulation(&data, philos))
		return (1);
	monitor_simulation(&data, philos);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	cleanup(&data, philos);
	return (0);
}
