/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:48:13 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/08 15:24:18 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//p1come p2espera p3come p4espera por dois(3 e 1)
void	initial_usleep(t_philo *philo)
{
	if (philo->id == philo->table->nbr_philos)//para o caso que ha 3 philosophers
		usleep(philo->table->time_to_eat * 2 * 1000);
	else if (philo->id % 2 == 0)
	{
		usleep(philo->table->time_to_eat *1000);
	}
}

