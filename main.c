/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/07 16:58:51 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	process_args(char *argv[], t_table **table)
{
	/*
		Do the classic argument parsing.
		Store the arguments in a struct
	*/

	(*table)->num_philos = ft_atoi(argv[1]);
	printf("Number of philosophers: %d\n",(*table)->num_philos);
	(*table)->philosopher = 0;
}

void	*thread_func(void *arg)
{
	t_table	*table = (t_table *)arg;

	printf("Thread %d started\n", table->philosopher);
	table->philosopher++;
	printf("This is philosopher no. %d\n", table->philosopher);
	
	return (NULL);
}

void	init_philos(t_table **table)
{
	/*
	pthread_t	philosopher[num_phil];
	*/
	t_table	*structure;
	t_table	*result;
	structure = *table;
	int i;
	int	err;
	pthread_t	phil_thread[(*table)->num_philos];

	printf("The philosopher value here is %d\n",structure->philosopher);
	i = 0;
	while (i < (*table)->num_philos)
	{
		err = pthread_create(&(phil_thread[i]), NULL, &thread_func, (void *)structure);
		i++;
	}
	i = 0;
	while (i < (*table)->num_philos)
	{
		err = pthread_join(phil_thread[i], (void **)&result);
		printf("Thread %d rejoined\n", i);
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
		init_philos(&table);
	}
	else
	{
		ft_putstr_fd("Wrong no. of args\n", 1);
	}
	return (0);
}
