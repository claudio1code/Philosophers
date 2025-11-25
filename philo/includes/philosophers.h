/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:36:00 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/25 14:56:35 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	philo_lock;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	int				num_philos;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	*forks;
	int				stop_simulation;
}	t_data;

int	parse_arguments(int argc, char **argv, t_data *data);

#endif
