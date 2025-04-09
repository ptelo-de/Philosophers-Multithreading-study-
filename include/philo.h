/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:23:51 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/09 13:24:04 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			theread_id;
	pthread_mutex_t		*one_fork;
	pthread_mutex_t		*two_fork;
	unsigned int		time_last_meal;
	unsigned int		meals_eaten;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	size_t				start_time;
	unsigned int		nbr_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		nbr_of_meals;
	unsigned int		philos_finished;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	unsigned int		extermination;
	pthread_mutex_t		print;
	pthread_mutex_t		life;
	pthread_mutex_t		meals;
	pthread_t			monitor;
	int					flag_life;
	int					flag_meals;
	int					flag_print;
}						t_table;

int				check_args(int argc, char *argv[]);
void			clear_mem(t_table *table);

int				init_table(int argc, char *argv[], t_table *table);

int				init_forks(t_table *table);
int				init_monitor(t_table *table);

int				init_philos(t_table *table);


int				create_threads(t_table *table);

void			initial_usleep(t_philo *philo);
void			*life_routine(void *arg);


void			*death_routine(void *arg);


void			ft_putstr_fd(char *s, int fd);
unsigned int	ft_atou(const char *nptr);
unsigned int			ft_my_time(void);


void			destroy_atributes(t_table	*table);
void			free_philos(t_table *table);
void			free_forks(t_table *table);

unsigned int	ft_my_time(void);
int				philo_wait(unsigned int time);
int				is_dead(t_table *table);
void			get_time_last_meal(t_philo *philo);
int				act(char *msg, t_philo *philo, unsigned int time);
void			meals_eaten_add(t_philo *philo);
int	mutex_printf(char *msg, t_table *table, t_philo *philo);
#endif