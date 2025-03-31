#include "../include/philo.h"

/**
 * @brief Routine executed by each philosopher thread.
 *
 * Simulates the lifecycle of a philosopher, including eating, sleeping, 
 * and thinking. The routine ends if the philosopher dies 
 * or if the simulation is terminated.
 *
 * @param arg Pointer to the philosopher structure.
 * @return NULL when the routine completes.
 */
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
		meals_iteration(philo);
		pthread_mutex_unlock(philo->two_fork);
		pthread_mutex_unlock(philo->one_fork);
		if (!act("is sleeping\n", philo, philo->table->time_to_sleep))
			break ;
		if (!act("is thinking\n", philo, philo->table->time_to_think))
			break ;
	}
	return (NULL);
}