#include "../include/philo.h"

/**
 * @brief Handles errors related to thread creation and sets
 * the extermination flag to indicate that the simulation must terminate.
 *
 * @param table Pointer to a t_table structure.
 */
void	error_pthread(t_table *table)
{
	printf("ERROR: Failed creating thread\n");
	pthread_mutex_lock(&table->life);
	table->extermination = 1;
	pthread_mutex_unlock(&table->life);
}

/**
 * @brief Joins all philosopher threads as well as the monitor thread.
 *
 * Waits for all philosopher and monitor threads to complete execution.
 *
 * @param table Pointer to a table structure.
 * @return 0 if all threads are successfully joined, -1 otherwise.
 */

int	threads_union(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].theread_id, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		return (-1);
	return (0);
}

/**
 * @brief Calculate the current time in milliseconds using `gettimeofday`
 * function.

 *
 * @return The current time in milliseconds.
 */

unsigned int	ft_my_time(void)
{
	unsigned int	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
void solo_philo(t_table *table)
{
	pthread_mutex_lock(table->philos[0].one_fork);
	act("has taken a fork\n", &(table->philos[0]), table->time_to_die);
	pthread_mutex_unlock(table->philos[0].one_fork);
	act("died\n", &(table->philos[0]), 0);
}

int	create_threads(t_table *table)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	table->start_time = ft_my_time();
	if (table->nbr_philos == 1)
		return (solo_philo(table), -1);
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].theread_id, NULL, &life_routine,
				&table->philos[i]) != 0)
		{
			error_pthread(table);
			j = 0;
			while (j++ < i)
				pthread_join(table->philos[j].theread_id, NULL);
			return (-1);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &death_routine, table) != 0)
		error_pthread(table);
	if (threads_union(table) == -1)
		return (-1);
	return (0);
}
