/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:35:45 by clados-s          #+#    #+#             */
/*   Updated: 2025/11/24 15:29:09 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int num_philos)
{
	int i;
	
	data->forks = malloc(sizeof(t_data) * num_philos);
}

int	main(int argc, char **argv)
{

}
