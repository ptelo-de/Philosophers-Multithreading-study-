/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:59:06 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/12 21:59:16 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_table *table)
{
	pthread_mutex_lock(&table->life);
	if (table->extermination)
	{
		pthread_mutex_unlock(&table->life);
		return (1);
	}
	pthread_mutex_unlock(&table->life);
	return (0);
}

static int	take_forks_for_odd_id(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->two_fork);
		if (mutex_printf("has taken a fork\n", philo->table, philo))
		{
			pthread_mutex_unlock(philo->two_fork);
			return (0);
		}
		pthread_mutex_lock(philo->one_fork);
		if (mutex_printf("has taken a fork\n", philo->table, philo))
		{
			pthread_mutex_unlock(philo->one_fork);
			pthread_mutex_unlock(philo->two_fork);
			return (0);
		}
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->one_fork);
		if (mutex_printf("has taken a fork\n", philo->table, philo))
		{
			pthread_mutex_unlock(philo->one_fork);
			return (0);
		}
		pthread_mutex_lock(philo->two_fork);
		if (mutex_printf("has taken a fork\n", philo->table, philo))
		{
			pthread_mutex_unlock(philo->two_fork);
			pthread_mutex_unlock(philo->one_fork);
			return (0);
		}
	}
	return (take_forks_for_odd_id(philo));
}

void	safe_fork_unlock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->two_fork);
		pthread_mutex_unlock(philo->one_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->one_fork);
		pthread_mutex_unlock(philo->two_fork);
	}
}

void	*life_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_dead(philo->table))
	{
		if (!take_forks(philo))
			break ;
		get_time_last_meal(philo);
		if (!act("is eating\n", philo, philo->table->time_to_eat))
		{
			safe_fork_unlock(philo);
			break ;
		}
		meals_eaten_add(philo);
		safe_fork_unlock(philo);
		if (!act("is sleeping\n", philo, philo->table->time_to_sleep))
			break ;
		if (!act("is thinking\n", philo, philo->table->time_to_think))
			break ;
	}
	return (NULL);
}
