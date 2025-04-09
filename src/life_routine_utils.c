/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:48:13 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/09 17:46:59 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_wait(unsigned int time)
{
	usleep(time * 1000);
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
	if (is_dead(philo->table))
		return (0);
	if (mutex_printf(msg, philo->table, philo))
		return (0);
	return (philo_wait(time));
}

void	meals_eaten_add(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meals);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->nbr_of_meals)
		philo->table->philos_finished++;
	pthread_mutex_unlock(&philo->table->meals);
}
