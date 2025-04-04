/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:59:06 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/04 02:22:12 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


static	void	initial_usleep(t_philo *philo)
{
	if (philo->id == philo->table->nbr_philos)
		usleep(philo->table->time_to_eat * 2);
	else if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat);
}

