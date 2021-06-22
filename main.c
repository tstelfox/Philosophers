/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/22 17:04:57 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_table **table, int num_philos)
{
	t_philo	philosophers[num_philos];
	int i;

	i = 0;
	while (i < num_philos)
	{
		philosophers[i].left = false;
		philosophers[i].right = false;
		philosophers[i].philosopher = i + 1;
		i++;
	}
	(*table)->philo = philosophers;
}

void	process_args(char *argv[], t_table **table)
{
	/*
		Do the classic argument parsing.
		Store the arguments in a struct
	*/
	(*table)->num_philos = ft_atoi(argv[1]);
	init_philos(table, (*table)->num_philos);
	// printf("Philosopher number three: |%d|\n", (*table)->philo[2].philosopher);
	// (*table)->to_die = ft_atoi(argv[2]);
	// (*table)->to_eat = ft_atoi(argv[3]);
	// (*table)->to_rest = ft_atoi(argv[4]);
	printf("Number of philosophers: %d\n",(*table)->num_philos);
	(*table)->philosopher = 1;
}

void	*thread_func(void *arg)
{
	t_table	*table = (t_table *)arg;
	int	left = table->philosopher - 1;
	int right = table->philosopher;

	if (table->philosopher == table->num_philos)
		right = 0;
	table->philosopher++;
	// printf("philosopher number: |%d|\n", table->philosopher);
	pthread_mutex_lock(&table->ch_stick[left]);
	table->philo[table->philosopher].left = true;
	if (table->philo[table->philosopher].left == true)
		printf("Philosopher no. %d picked up the left chopstick\n", table->philo[table->philosopher].philosopher);
	table->philo[table->philosopher].left = false;
	if (table->philo[table->philosopher].left == false)
		printf("Philosopher no. %d dropped the left chopstick\n", table->philo[table->philosopher].philosopher);
	pthread_mutex_unlock(&table->ch_stick[left]);
	pthread_mutex_lock(&table->ch_stick[right]);
	table->philo[table->philosopher].right = true;
	if (table->philo[table->philosopher].right == true)
		printf("Philosopher no. %d picked up the right chopstick\n", table->philo[table->philosopher].philosopher);
	table->philo[table->philosopher].right = false;
	if (table->philo[table->philosopher].right == false)
		printf("Philosopher no. %d dropped the right chopstick\n", table->philo[table->philosopher].philosopher);
	pthread_mutex_unlock(&table->ch_stick[right]);

	return (NULL);
}

void	init_threads(t_table **table)
{
	/*
	pthread_t	philosopher[num_phil];
	*/
	t_table	*structure;
	t_table	*result;
	int i;
	int	err;
	pthread_t	phil_thread[(*table)->num_philos];
	pthread_mutex_t	stick_temp[(*table)->num_philos];

	structure = *table;
	printf("The philosopher value here is %d\n",structure->philosopher);

	(*table)->ch_stick = stick_temp;
	i = 0;
	while (i < (*table)->num_philos)
	{
		pthread_mutex_init(&(*table)->ch_stick[i], NULL);
		err = pthread_create(&(phil_thread[i]), NULL, &thread_func, (void *)structure);
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
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (argc == 5 || argc == 6 || argc == 2)
	{
		process_args(argv, &table);
		// ft_putstr_fd("heya\n", 1);
		init_threads(&table);
	}
	else
	{
		ft_putstr_fd("Wrong no. of args\n", 1);
	}
	return (0);
}
