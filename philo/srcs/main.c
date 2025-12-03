/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:37:17 by clados-s          #+#    #+#             */
/*   Updated: 2025/12/03 10:50:46 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data))
		return (1);
	printf("Numero de Philos: %d\n", data.num_philos);
	printf("Tempo para morrer: %lld\n", data.time_to_die);
	printf("Tempo para comer: %lld\n", data.time_to_eat);
	printf("Tempo para dormir: %lld\n", data.time_to_sleep);
	return (0);
}