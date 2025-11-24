/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:36:00 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/24 15:19:48 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	philo_lock;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	p
} t_philo;

typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	*forks;
	int				stop_simulation;
} t_data;


#endif
