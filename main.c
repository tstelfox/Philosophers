/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/22 19:49:17 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	**init_philos(t_table **table, int num_philos)
{
	t_philo	**philosophers;
	int i;

	philosophers = malloc(sizeof(t_philo *) * num_philos);
	philosophers[num_philos] = NULL;
	/*
		Have to also put the time_to_stuff in here as well at some point
	 */
	i = 0;
	while (i < num_philos)
	{
		philosophers[i] = malloc(sizeof(t_philo));
		philosophers[i]->left = false;
		philosophers[i]->right = false;
		philosophers[i]->philosopher = i + 1;
		philosophers[i]->table = *table;
		i++;
	}
	return(philosophers);
}

t_philo	**process_args(char *argv[], t_table **table)
{
	t_philo **philos;
	/*
		Do the classic argument parsing.
		Store the arguments in a struct
	*/
	(*table)->num_philos = ft_atoi(argv[1]);
	// printf("Philosopher number three: |%d|\n", (*table)->philo[2].philosopher);
	// (*table)->to_die = ft_atoi(argv[2]);
	// (*table)->to_eat = ft_atoi(argv[3]);
	// (*table)->to_rest = ft_atoi(argv[4]);
	printf("Number of philosophers: %d\n",(*table)->num_philos);
	// (*table)->philosopher = 0;
	philos = init_philos(table, (*table)->num_philos);
	return (philos);
}

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	printf("philosopher number: |%d|\n", philo->philosopher);
	pthread_mutex_lock(&philo->table->ch_stick[left]);
	philo[philo->philosopher].left = true;
	if (philo[philo->philosopher].left == true)
		printf("Philosopher no. %d picked up the left chopstick\n", philo->philosopher);
	philo[philo->philosopher].left = false;
	if (philo[philo->philosopher].left == false)
		printf("Philosopher no. %d dropped the left chopstick\n", philo->philosopher);
	pthread_mutex_unlock(&philo->table->ch_stick[left]);
	pthread_mutex_lock(&philo->table->ch_stick[right]);
	philo[philo->philosopher].right = true;
	if (philo[philo->philosopher].right == true)
		printf("Philosopher no. %d picked up the right chopstick\n", philo->philosopher);
	philo[philo->philosopher].right = false;
	if (philo[philo->philosopher].right == false)
		printf("Philosopher no. %d dropped the right chopstick\n", philo->philosopher);
	pthread_mutex_unlock(&philo->table->ch_stick[right]);

	return (NULL);
}

void	init_threads(t_philo **philo, t_table **table)
{
	/*
	pthread_t	philosopher[num_phil];
	*/
	t_philo	*structure;
	t_philo	*result;
	int i;
	int	err;
	pthread_t	phil_thread[(*table)->num_philos];
	pthread_mutex_t	stick_temp[(*table)->num_philos];

	structure = *philo;
	printf("The philosopher value here is %d\n",structure->philosopher);

	(*table)->ch_stick = stick_temp;
	i = 0;
	while (i < (*table)->num_philos)
	{
		pthread_mutex_init(&(*table)->ch_stick[i], NULL);
		// (*table)->philosopher = i + 1;
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
}

int	main(int argc, char *argv[])
{
	t_table	*table;
	t_philo **philo;

	table = malloc(sizeof(t_table));
	if (argc == 5 || argc == 6 || argc == 2)
	{
		philo = process_args(argv, &table);
		// ft_putstr_fd("heya\n", 1);
		init_threads(philo, &table);
	}
	else
	{
		ft_putstr_fd("Wrong no. of args\n", 1);
	}
	return (0);
}
