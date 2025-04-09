/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:15:57 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/09 13:15:58 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Validates the arguments provided to the program.
 *
 * Checks if each argument contains only numeric characters.
 * '+' or '-' are not accepted.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of argument strings.
 * @return 0 if all arguments are valid, -1 otherwise.
 */
int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
			{
				ft_putstr_fd("ERROR: Invalid format!\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
