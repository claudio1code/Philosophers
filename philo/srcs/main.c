/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:37:17 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/03 17:24:27 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL)
		|| pthread_mutex_init(&data->monitor_lock, NULL))
	{
		free(data->forks);
		return (1);
	}
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philosophers(t_philo *philo)
{
	philo->philo_lock = malloc(sizeof(pthread_mutex_t) * );
	
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data))
		return (1);
	if (init_data(&data))
		return (1);
	
	printf("Numero de Philos: %d\n", data.num_philos);
	printf("Tempo para morrer: %lld\n", data.time_to_die);
	printf("Tempo para comer: %lld\n", data.time_to_eat);
	printf("Tempo para dormir: %lld\n", data.time_to_sleep);
	return (0);
}