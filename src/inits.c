/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:08:36 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/09 17:51:58 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Initializes the t_table structure with the input parameters.
 * Check if all the input are greater than 0.
 * Also calculates the time to think for each philosopher.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments.
 * @param table Pointer to the t_table structure to be initialized.
 * @return 0 on success, -1 if an error occurs.
 */

int	init_table(int argc, char *argv[], t_table *table)
{
	table->nbr_philos = ft_atou(argv[1]);
	table->time_to_die = ft_atou(argv[2]);
	table->time_to_eat = ft_atou(argv[3]);
	table->time_to_sleep = ft_atou(argv[4]);
	if (argc == 6)
	{
		table->nbr_of_meals = ft_atou(argv[5]);
		if (table->nbr_of_meals == 0)
			return (-1);
	}
	if (table->time_to_die == 0 || table->time_to_eat == 0
		|| table->time_to_sleep == 0 || table->nbr_philos == 0)
		return (-1);
	if ((table->nbr_philos % 2)
		&& table->time_to_sleep < table->time_to_eat * 2)
	{
		table->time_to_think = table->time_to_eat * 2 - table->time_to_sleep;
	}
	return (0);
}

/**
 * @brief Initializes the mutexes (forks) for the philosophers.
 *
 * Allocates memory for the array of mutex adresses
 * and initializes each mutex.
 *
 * @param table Pointer to the t_table structure
 * @return 0 on success, -1 if an error occurs.
 */
int	init_forks(t_table *table)
{
	unsigned int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Inits mutexes for managing philosopher life, 
 * printing output, and tracking meals.
 *
 * @param table Pointer to a t_table structure 
 * @return 0 on success, -1 if an error occurs.
 */
int	init_monitor(t_table *table)
{
	table->monitor = 0;
	if (pthread_mutex_init(&table->life, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_life = 1;
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_print = 1;
	if (pthread_mutex_init(&table->meals, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_meals = 1;
	return (0);
}

static void	initial_fork_asignation(t_philo *philo, int i)
{
	if (philo->id == 1)
	{
		philo->one_fork = &philo->table->forks[philo->table->nbr_philos - 1];
		philo->two_fork = &philo->table->forks[0];
	}
	else
	{
		philo->one_fork = &philo->table->forks[i - 1];
		philo->two_fork = &philo->table->forks[i];
	}
}

/**
 * @brief Initializes the philosopher structures
 * and assigns forks to each philosopher.
 *
 * @param table Pointer to the t_table structure
 * @return 0 on success, -1 on failure
 */
int	init_philos(t_table *table)
{
	unsigned int	i;

	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
		return (-1);
	i = -1;
	while (table->nbr_philos > ++i)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].time_last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].theread_id = 0;
		initial_fork_asignation(&table->philos[i], i);
	}
	return (0);
}
