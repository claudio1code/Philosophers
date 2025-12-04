/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:35:45 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/04 17:23:00 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_data *data, t_philo *philos)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &philo_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	philosopher_has_died(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&philos[i].philo_lock);
		if (get_time() - philos[i].last_meal_time > data->time_to_die)
		{
			print_action(&philos[i], "died 💀");
			pthread_mutex_unlock(&philos[i].philo_lock);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].philo_lock);
		i++;
	}
	return (0);
}

static int	all_philos_have_eaten(t_data *data, t_philo *philos)
{
	int	i;
	int	finished_philos;

	if (data->eat_count_max <= 0)
		return (0);
	i = 0;
	finished_philos = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&philos[i].philo_lock);
		if (philos[i].meals_eaten >= data->eat_count_max)
			finished_philos++;
		pthread_mutex_unlock(&philos[i].philo_lock);
		i++;
	}
	if (finished_philos == data->num_philos)
		return (1);
	return (0);
}

void	monitor_simulation(t_data *data, t_philo *philos)
{
	while (1)
	{
		if (philosopher_has_died(data, philos)
			|| all_philos_have_eaten(data, philos))
		{
			pthread_mutex_lock(&data->monitor_lock);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->monitor_lock);
			return ;
		}
		usleep(1000);
	}
}
