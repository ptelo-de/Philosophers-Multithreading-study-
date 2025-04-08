/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:48:13 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/07 01:27:02 by ptelo-de         ###   ########.fr       */
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
		printf("initial sleep\n\n");
		usleep(philo->table->time_to_eat *1000);
		printf("philo %u after initial sleep %lu\n",philo->id, 	ft_my_time() - philo->table->start_time);
	}
}

