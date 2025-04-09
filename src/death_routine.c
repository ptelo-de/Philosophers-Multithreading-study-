/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:36:08 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/09 17:58:57 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	dead_msg(t_table *table, unsigned int *i)
{
	printf("%lu %d died\n", ft_my_time() - table->start_time,
		table->philos[*i].id);
}

int	extreminate_if_finished(t_table *table)
{
	pthread_mutex_lock(&table->meals);
	if (table->philos_finished == table->nbr_philos)
	{
		pthread_mutex_lock(&table->life);
		table->extermination = 1;
		pthread_mutex_unlock(&table->life);
		pthread_mutex_unlock(&table->meals);
		return (1);
	}
	pthread_mutex_unlock(&table->meals);
	return (0);
}

void	*death_routine(void *arg)
{
	t_table			*table;
	unsigned int	i;

	table = (t_table *)arg;
	while (!table->extermination)
	{
		i = -1;
		while (table->nbr_philos > ++i)
		{
			pthread_mutex_lock(&table->life);
			if (table->philos[i].time_last_meal != 0
				&& (ft_my_time() - table->philos[i].time_last_meal) \
				> table->time_to_die)
			{
				table->extermination = 1;
				pthread_mutex_unlock(&table->life);
				dead_msg(table, &i);
				return (NULL);
			}
			pthread_mutex_unlock(&table->life);
		}
		if (extreminate_if_finished(table))
			break ;
	}
	return (NULL);
}
