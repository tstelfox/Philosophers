/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/27 20:09:48 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philos(t_table **table, int num_philos)
{
	t_philo	*philosophers;
	struct timeval now;
	int i;

	gettimeofday(&now, NULL);
	philosophers = malloc(sizeof(t_philo) * (num_philos));
	i = 0;
	while (i < num_philos)
	{
		philosophers[i].lock_print = malloc(sizeof(pthread_mutex_t));
		philosophers[i].lock_eat = malloc(sizeof(pthread_mutex_t));
		philosophers[i].state = THINKING;
		philosophers[i].philosopher = i + 1;
		philosophers[i].meals_num = 0;
		philosophers[i].table = *table;
		philosophers[i].last_ate = now;
		i++;
	}
	return(philosophers);
}

int		parse_input(char *input)
{
	int	i;
	
	i = 0;
	while(input[i])
	{
		if (!ft_isdigit(input[i]))
			return (0);
		i++;
	}
	i = ft_atoi(input);
	if (i <= 0)
		return (0);
	return (i);
}

t_philo	*process_args(int argc, char *argv[], t_table **table)
{
	t_philo *philos;
	(*table)->lock_action = malloc(sizeof(pthread_mutex_t));
	(*table)->lock_death = malloc(sizeof(pthread_mutex_t));
	(*table)->num_philos = parse_input(argv[1]);
	(*table)->to_die = parse_input(argv[2]);
	(*table)->to_eat = parse_input(argv[3]);
	(*table)->to_sleep = parse_input(argv[4]);
	(*table)->dinner_over = false;
	(*table)->sum1dead = false;
	if (argc == 6)
		(*table)->rounds = parse_input(argv[5]);
	else
		(*table)->rounds = -1;
	if (!(*table)->num_philos || !(*table)->to_die || !(*table)->to_eat || 
		!(*table)->to_sleep || !(*table)->rounds)
		return (NULL);
	philos = init_philos(table, (*table)->num_philos);
	return (philos);
}

void	init_threads(t_philo **philo, t_table **table)
{
	t_philo	*structure;
	t_philo	*result;
	int i;
	int	err;
	pthread_t	phil_thread[(*table)->num_philos];
	pthread_mutex_t	stick_temp[(*table)->num_philos];

	structure = *philo;

	pthread_mutex_init((*table)->lock_action, NULL);
	pthread_mutex_init((*table)->lock_death, NULL);
	(*table)->ch_stick = stick_temp;
	i = 0;
	gettimeofday(&(*table)->start_time, NULL);
	while (i < (*table)->num_philos)
	{
		pthread_mutex_init(structure[i].lock_print, NULL);
		pthread_mutex_init(structure[i].lock_eat, NULL);
		pthread_mutex_init(&(*table)->ch_stick[i], NULL);
		i++;
	}
	i = 0;
	while (i < (*table)->num_philos)
	{
		err = pthread_create(&(phil_thread[i]), NULL, &thread_func, (void *)&structure[i]);
		i++;
	}
	monitor_func(*philo);
	i = 0;
	while (i < (*table)->num_philos)
	{
		err = pthread_join(phil_thread[i], (void **)&result);
		pthread_mutex_destroy(&(*table)->ch_stick[i]);
		pthread_mutex_destroy(structure[i].lock_eat);
		pthread_mutex_destroy(structure[i].lock_print);
		i++;
	}
	pthread_mutex_destroy((*table)->lock_action);
	pthread_mutex_destroy((*table)->lock_death);
}

int	main(int argc, char *argv[])
{
	t_table	*table;
	t_philo *philo;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		table = malloc(sizeof(t_table));
		philo = process_args(argc, argv, &table);
		if (philo == NULL)
		{
			printf("Plato says your input's fucked\n");
			free(table);
			return (1);
		}
		init_threads(&philo, &table);
		free_all(philo, table);
	}
	else
		ft_putstr_fd("Wrong no. of args\n", 1);
	system("leaks philo");
	return (0);
}
