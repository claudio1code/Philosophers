/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:35:45 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/26 15:50:05 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_global_data(t_data *data)
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

static int	init_philosophers(t_philo **philos, t_data *data)
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
	/*pthread_t	*threads*/

	if (parse_arguments(argc, argv, &data))
		return (1);
	if (init_philosophers(&philos, &data))
	{
		printf("Error: Falied to initialize philosophers.\n");

		return (1);
	}
	if (init_global_data(&data))
		return (1);
	printf("Sucesso! %d filósofos inicializados.\n", data.num_philos);
	printf("Filósofo 1: Garfo Esq %p, Garfo Dir %p\n",
		(void *)philos[0].left_fork, (void *)philos[0].right_fork);
	printf("Último Filósofo: Garfo Esq %p, Garfo Dir %p\n",
		(void *)philos[data.num_philos - 1].left_fork,
		(void *)philos[data.num_philos - 1].right_fork);
}
