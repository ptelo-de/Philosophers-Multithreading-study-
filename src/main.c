/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:23:36 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/09 17:52:42 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("ERROR: Wrong number of elements\n", 2), 1);
	clear_mem(&table);
	if (check_args(argc, argv) == -1 || init_table(argc, argv, &table) == -1)
		return (5);
	if (init_forks(&table) == -1 || init_monitor(&table) == -1)
	{
		destroy_atributes(&table);
		return (2);
	}
	if (init_philos(&table) == -1)
	{
		destroy_atributes(&table);
		return (3);
	}
	if (create_threads(&table) == -1)
	{
		destroy_atributes(&table);
		return (4);
	}
	destroy_atributes(&table);
	return (0);
}
