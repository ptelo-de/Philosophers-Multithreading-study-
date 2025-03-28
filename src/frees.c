#include "../include/philo.h"

/**
 * @brief Frees all allocated memory and destroys mutexes in the simulation.
 *
 * @param table Pointer to a t_table structure.
 */

void	destroy_atributes(t_table	*table)
{
	if (table->philos)
		free_philos(table);
	if (table->forks)
		free_forks(table);
	if (table->flag_life)
		pthread_mutex_destroy(&table->life);
	if (table->flag_print)
		pthread_mutex_destroy(&table->print);
	if (table->flag_meals)
		pthread_mutex_destroy(&table->meals);
}

/**
 * @brief Frees memory allocated for the array of adresses of each t_philo structure.
 * and resets their fields.
 * 
 * @param table Pointer to a t_table structure.
 */
void	free_philos(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].one_fork = NULL;
		table->philos[i].two_fork = NULL;
		table->philos[i].table = NULL;
		i++;
	}
	free(table->philos);
	table->philos = NULL;
}

/**
 * @brief Destroys fork mutexes and frees the t_fork pointer.
 * 
 * @param table Pointer to a t_table structure.
 */
void	free_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
}