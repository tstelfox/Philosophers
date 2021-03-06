/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/29 11:53:12 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutex(t_philo *philo, int i, t_table *table)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&(*table).ch_stick[i]);
		pthread_mutex_destroy(philo[i].lock_eat);
		pthread_mutex_destroy(philo[i].lock_print);
		i--;
	}
	return (0);
}

int	threads_start(pthread_t *phil_thread, t_philo *philo, t_table *table)
{
	int	i;
	int	fail1;
	int	fail2;
	int	fail3;

	i = 0;
	while (i < (*table).num_philos)
	{
		fail1 = pthread_mutex_init(philo[i].lock_print, NULL);
		fail2 = pthread_mutex_init(philo[i].lock_eat, NULL);
		fail3 = pthread_mutex_init(&(*table).ch_stick[i], NULL);
		if (fail1 || fail2 || fail3)
			return (destroy_mutex(philo, i, table));
		i++;
	}
	i = 0;
	while (i < (*table).num_philos)
	{
		if (pthread_create(&(phil_thread[i]), NULL, &thread_func,
				(void *)&philo[i]))
			return (0);
		i++;
	}
	return (1);
}

void	threads_end(pthread_t *phil_thread, t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < (*table).num_philos)
	{
		pthread_join(phil_thread[i], NULL);
		pthread_mutex_destroy(&(*table).ch_stick[i]);
		pthread_mutex_destroy(philo[i].lock_eat);
		pthread_mutex_destroy(philo[i].lock_print);
		i++;
	}
	pthread_mutex_destroy((*table).lock_action);
	pthread_mutex_destroy((*table).lock_death);
}

int	init_threads(t_philo **philo, t_table **table)
{
	t_philo			*structure;
	pthread_t		*phil_thread;
	pthread_mutex_t	*stick_temp;

	phil_thread = malloc(sizeof(pthread_t) * (*table)->num_philos);
	stick_temp = malloc(sizeof(pthread_mutex_t) * (*table)->num_philos);
	if (!phil_thread || !stick_temp)
		return (0);
	structure = *philo;
	if (pthread_mutex_init((*table)->lock_action, NULL)
		|| pthread_mutex_init((*table)->lock_death, NULL))
		return (0);
	(*table)->ch_stick = stick_temp;
	gettimeofday(&(*table)->start_time, NULL);
	if (!threads_start(phil_thread, structure, *table))
		return (0);
	monitor_func(*philo);
	threads_end(phil_thread, structure, *table);
	free(phil_thread);
	free(stick_temp);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_table	*table;
	t_philo	*philo;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		table = malloc(sizeof(t_table));
		if (!table)
			return (1);
		philo = process_args(argc, argv, &table);
		if (philo == NULL)
		{
			printf("Plato says your input's fucked\n");
			free(table);
			return (1);
		}
		if (!init_threads(&philo, &table))
			printf("Something really fucked up\n");
		free_all(philo, table);
	}
	else
		ft_putstr_fd("Wrong no. of args\n", 1);
	return (0);
}
