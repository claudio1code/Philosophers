/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:50:46 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/04 17:14:10 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *str)
{
	long long	time;
	int			stop;

	pthread_mutex_lock(&philo->data->monitor_lock);
	stop = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->monitor_lock);
	if (!stop)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
}

void	cleanup(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->monitor_lock);
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&philos[i].philo_lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(philos);
}
