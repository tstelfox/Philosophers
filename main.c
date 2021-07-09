/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/09 16:19:46 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philos(t_table **table, int num_philos)
{
	t_philo	*philosophers;
	int i;

	philosophers = malloc(sizeof(t_philo) * (num_philos));
	i = 0;
	while (i < num_philos)
	{
		philosophers[i].state = THINKING;
		philosophers[i].philosopher = i + 1;
		philosophers[i].left = false;
		philosophers[i].right = false;
		philosophers[i].last_ate = 0;
		philosophers[i].meals_num = 0;
		philosophers[i].table = *table;
		i++;
	}
	return(philosophers);
}

t_philo	*process_args(int argc, char *argv[], t_table **table)
{
	t_philo *philos;
	/*
		Do the classic argument parsing.
	*/
	(*table)->lock_action = malloc(sizeof(pthread_mutex_t));
	(*table)->lock_death = malloc(sizeof(pthread_mutex_t));
	(*table)->num_philos = ft_atoi(argv[1]);
	(*table)->to_die = ft_atoi(argv[2]);
	(*table)->to_eat = ft_atoi(argv[3]);
	(*table)->to_sleep = ft_atoi(argv[4]);
	(*table)->dinner_over = false;
	(*table)->sum1dead = false;
	if (argc == 6)
		(*table)->rounds = ft_atoi(argv[5]);
	else
		(*table)->rounds = 0;
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

	(*table)->ch_stick = stick_temp;
	i = 0;
	gettimeofday(&(*table)->start_time, NULL);
	pthread_mutex_init((*table)->lock_action, NULL);
	pthread_mutex_init((*table)->lock_death, NULL);
	while (i < (*table)->num_philos)
	{
		pthread_mutex_init(&(*table)->ch_stick[i], NULL);
		err = pthread_create(&(phil_thread[i]), NULL, &thread_func, (void *)&structure[i]);
		i++;
	}
	i = 0;
	while (i < (*table)->num_philos)
	{
		err = pthread_join(phil_thread[i], (void **)&result);
		printf("Thread %d rejoined\n", i);
		pthread_mutex_destroy(&(*table)->ch_stick[i]);
		i++;
	}
	pthread_mutex_destroy((*table)->lock_action);
	pthread_mutex_destroy((*table)->lock_death);
}

int	main(int argc, char *argv[])
{
	t_table	*table;
	t_philo *philo;

	table = malloc(sizeof(t_table));
	if (argc == 5 || argc == 6)
	{
		philo = process_args(argc, argv, &table);
		init_threads(&philo, &table);
	}
	else
	{
		ft_putstr_fd("Wrong no. of args\n", 1);
	}
	return (0);
}
