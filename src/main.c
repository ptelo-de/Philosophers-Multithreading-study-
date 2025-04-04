/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:23:36 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/04 16:17:03 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
void print_stuff(t_table *info)
{
	int i = 0;
	t_table table = *info;
	
	while (i < (int)table.nbr_philos)
	{
		printf("philo %d\nfork1; %p\nfork2:%p\n\n", i + 1, \
		table.philos[i].one_fork, \
		table.philos[i].two_fork);
		i++;
	}
	i = 0;
	printf("\n");
	while (i < (int)table.nbr_philos)
	{
		printf("philo %d\nfork1; %d\nfork2:%d\n\n", i + 1, \
		table.philos[i].one_fork_number, \
		table.philos[i].two_fork_number);
		i++;
	}
}
int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("ERROR: Wrong number of elements\n", 2), 1);
	clear_mem(&table);
	if (check_args(argc, argv) == -1 || init_table(argc, argv, &table) == -1
		|| init_forks(&table) == -1 || init_monitor(&table) == -1)
	{
		destroy_atributes(&table);
		return (2);
	}
	if (init_philos(&table) == -1)
	{
		destroy_atributes(&table);
		return (3);
	}
	print_stuff(&table);
	if (create_threads(&table) == -1)
	{
		destroy_atributes(&table);
		return (4);
	}
	destroy_atributes(&table); //fix this so you dont fuck pc
	return (0);
}
