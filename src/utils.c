/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:14:51 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/09 17:44:57 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Converts a string to an unsigned integer.
 * @param nptr Pointer to the string to be converted.
 * @return The converted unsigned integer.
 */
unsigned int	ft_atou(const char *nptr)
{
	unsigned int	i;
	unsigned int	sign;
	unsigned int	final_nr;

	sign = 1;
	final_nr = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		final_nr = (final_nr * 10) + (nptr[i] - '0');
		i++;
	}
	return (final_nr * sign);
}

/**
 * @brief Writes a string to the specified file descriptor.
 *
 * @param s Pointer to the string to be written.
 * @param fd File descriptor where the string will be written.
 */
void	ft_putstr_fd(char *s, int fd)
{
	int	idx;

	idx = 0;
	while (s[idx])
	{
		write(fd, &s[idx], 1);
		idx++;
	}
}

int	mutex_printf(char *msg, t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->print);
	pthread_mutex_lock(&table->life);
	if (table->extermination == 0)
	{
		printf("%lu %d ", ft_my_time() - philo->table->start_time, philo->id);
		printf("%s", msg);
		pthread_mutex_unlock(&table->life);
		pthread_mutex_unlock(&table->print);
		return (0);
	}
	pthread_mutex_unlock(&table->life);
	pthread_mutex_unlock(&table->print);
	return (1);
}

/**
 * @brief initializes values in the stack memory.
 *
 * Integers are initialized to 0, 
 * and pointers are initialized to NULL.
 *
 * @param table the adress of t_table.
 * @return void.
 */
void	clear_mem(t_table *table)
{
	table->extermination = 0;
	table->flag_life = 0;
	table->flag_meals = 0;
	table->flag_print = 0;
	table->forks = NULL;
	table->nbr_of_meals = 0;
	table->nbr_philos = 0;
	table->philos = NULL;
	table->philos_finished = 0;
	table->start_time = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->time_to_think = 0;
}
