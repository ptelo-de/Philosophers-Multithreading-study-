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

