#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("ERROR: Wrong number of elements\n", 2), 1);
	clean_mem(&table);
	if (check_args(argc, argv) == -1 || init_table(argc, argv, &table) == -1
		|| init_forks(&table) == -1 || init_monitor(&table) == -1)
	{
		destroy_atributes(&table);
		return (2);
	}
	if (init_philos(&table) == -1)
	{
		destroy_atributes(&table);
		return (3);
	}
	if (init_threads(&table) == -1)
	{
		destroy_atributes(&table);
		return (4);
	}
	//free_all(&table);
	//return (0);
}
