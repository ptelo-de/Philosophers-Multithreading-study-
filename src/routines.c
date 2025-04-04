/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:59:06 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/04 16:14:46 by ptelo-de         ###   ########.fr       */
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

int	take_forks(t_philo *philo)
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
	return (1);
}

void	get_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->life);
	philo->time_last_meal = ft_my_time();
	pthread_mutex_unlock(&philo->table->life);
}

int	act(char *msg, t_philo *philo, unsigned int time)
{
	unsigned int	elapsed_time;
	unsigned int	interval;

	elapsed_time = 0;
	interval = 6;
	if (is_dead(philo->table))
		return (0);
	if (mutex_printf(msg, philo->table, philo))
		return (0);
	while (elapsed_time < time)
	{
		usleep(interval * 1000);
		elapsed_time += interval;
		if (is_dead(philo->table))
			return (0);
	}
	return (1);
}
void	meals_eaten_add(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meals);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->nbr_of_meals)
		philo->table->philos_finished++;
	pthread_mutex_unlock(&philo->table->meals);
}

void	*life_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_usleep(philo);
	while (!is_dead(philo->table))
	{
		if (!take_forks(philo))
			break ;
		get_time_last_meal(philo);
		if (!act("is eating\n", philo, philo->table->time_to_eat))
		{
			pthread_mutex_unlock(philo->two_fork);
			pthread_mutex_unlock(philo->one_fork);
			break ;
		}
		meals_eaten_add(philo);
		pthread_mutex_unlock(philo->two_fork);
		pthread_mutex_unlock(philo->one_fork);
		if (!act("is sleeping\n", philo, philo->table->time_to_sleep))
			break ;
		if (!act("is thinking\n", philo, philo->table->time_to_think))
			break ;
	}
	return (NULL);
}
void	dead_msg(t_table *table, unsigned int *i)
{
	pthread_mutex_unlock(&table->life);
	printf("%lu %d died\n", ft_my_time() - table->start_time,
		table->philos[*i].id);
}

//int	extreminate_if_finished(t_table *table)
//{
//	pthread_mutex_lock(&table->meals);
//	if (table->philos_finished == table->nbr_philos)
//	{
//		table->extermination = 1;
//		pthread_mutex_unlock(&table->life);
//		pthread_mutex_unlock(&table->meals);
//		return (1);
//	}
//	pthread_mutex_unlock(&table->life);
//	pthread_mutex_unlock(&table->meals);
//	return (0);
//}
void	*death_routine(void *arg)
{
	t_table			*table;
	unsigned int	i;

	table = (t_table *)arg;
	while (!table->extermination)
	{
		i = 0;
		pthread_mutex_lock(&table->life);
		while (table->nbr_philos > i)
		{
			if ((ft_my_time() - table->philos[i].time_last_meal) \
				> table->time_to_die)
			{
				table->extermination = 1;
				dead_msg(table, &i);
				return (NULL);
			}
			i++;
		}
		//if (extreminate_if_finished(table))
		//	break ;
	}
	return (NULL);
}
