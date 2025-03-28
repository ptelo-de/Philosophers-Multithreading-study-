#include "../include/philo.h"

/**
 * @brief initializes values in the stack memory.
 *
 * Integers are initialized to 0, 
 * and pointers are initialized to NULL.
 *
 * @param table the adress of t_table.
 * @return void.
 */
void clear_mem(t_table *table)
{
	table->extermination = 0;
	table->flag_life = 0;
	table->flag_meals = 0;
	table->flag_print = 0;
	table->forks = NULL;
	table->nbr_of_meals = 0;
	table->nbr_philos = 0;
	table->philos = NULL;
	table->philos_eaten = 0;
	table->start_time = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->time_to_think = 0;
}

/**
 * @brief Initializes the t_table structure with the input parameters.
 * Check if all the input are greater than 0.
 * Also calculates the time to think for each philosopher.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments.
 * @param table Pointer to the t_table structure to be initialized.
 * @return 0 on success, -1 if an error occurs.
 */
int	init_table(int argc, char *argv[], t_table *table)
{
	table->nbr_philos = ft_atou(argv[1]);
	table->time_to_die = ft_atou(argv[2]);
	table->time_to_eat = ft_atou(argv[3]);
	table->time_to_sleep = ft_atou(argv[4]);
	if (argc == 6)
	{
		table->nbr_of_meals = ft_atou(argv[5]);
		if (table->nbr_of_meals == 0)
			return (-1);
	}
	if (table->time_to_die == 0 || table->time_to_eat == 0
		|| table->time_to_sleep == 0 || table->nbr_philos == 0)
		return (-1);
	if (table->nbr_philos == 1)
	{
		usleep(table->time_to_die * 1000);
		printf("0 1 was taken a fork\n%d 1 died\n", table->time_to_die); //as mensagens nao deviam estar separadas?
		return (-1);
	}
	else
		table->time_to_think = 100; // change this, how to calculate?
	return (0);
}

/**
 * @brief Initializes the mutexes (forks) for the philosophers.
 *
 * Allocates memory for the array of mutex adresses
 * and initializes each mutex.
 *
 * @param table Pointer to the t_table structure
 * @return 0 on success, -1 if an error occurs.
 */
int	init_forks(t_table *table)
{
	unsigned int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	i = 0;
	while (table->nbr_philos > i)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}
/**
 * @brief Inits mutexes for managing philosopher life, 
 * printing output, and tracking meals.
 *
 * @param table Pointer to a t_table structure 
 * @return 0 on success, -1 if an error occurs.
 */
int	init_monitor(t_table *table)
{
	if (pthread_mutex_init(&table->life, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_life = 1;
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_print = 1;
	if (pthread_mutex_init(&table->meals, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_meals = 1;
	return (0);
}

/**
 * @brief Initializes the philosopher structures
 * and assigns forks to each philosopher.
 *
 * @param table Pointer to the t_table structure
 * @return 0 on success, -1 on failure
 */
int	init_philos(t_table *table)
{
	unsigned int	idx;

	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
		return (-1);
	idx = 0;
	while (table->nbr_philos > idx)
	{
		table->philos[idx].id = idx + 1;
		table->philos[idx].meals_eaten = 0;
		table->philos[idx].time_last_meal = 0;
		table->philos[idx].table = table;
		table->philos[idx].theread_id = 0;
		if (table->philos[idx].id == 1)
			table->philos[0].two_fork = &table->forks[table->nbr_philos - 1];
		else
			table->philos[idx].two_fork = &table->forks[idx - 1];
		table->philos[idx].one_fork = &table->forks[idx];
		idx++;
	}
	return (0);
}
