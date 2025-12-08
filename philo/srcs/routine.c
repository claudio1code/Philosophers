/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:37:53 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/08 18:06:09 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	which_philo(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s)
{
	if (p->id % 2 == 0)
	{
		*f = p->left_fork;
		*s = p->right_fork;
	}
	else
	{
		*f = p->right_fork;
		*s = p->left_fork;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	which_philo(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork 🍴");
	if (philo->data->num_philos == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_action(philo, "has taken a fork 🍴");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_lock);
	print_action(philo, "is eating 🍝");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->monitor_lock);
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&philo->data->monitor_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->monitor_lock);
		philo_eat(philo);
		print_action(philo, "is sleeping 💤");
		usleep(philo->data->time_to_sleep * 1000);
		print_action(philo, "is thinking 💭");
		usleep();
	}
	return (NULL);
}
