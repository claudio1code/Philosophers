/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:50:46 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/26 17:35:56 by clados-s         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->stop_simulation)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

static void	which_philo(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s)
{
		if (p->id % 2 == 0)
	{
		*f = philo->left_fork;
		*s = philo->right_fork;
	}
	else
	{
		*f = philo->right_fork;
		*s = philo->left_fork;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	which_philo(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork🍴");
	if (philo->data->num_philos == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_action(philo, "has taken a fork🍴");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_lock);
	print_action(philo, "is eating 💭");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}
