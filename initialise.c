/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 22:05:34 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/28 15:40:28 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philos(t_table **table, int num_philos)
{
	t_philo			*philosophers;
	struct timeval	now;
	int				i;

	gettimeofday(&now, NULL);
	philosophers = malloc(sizeof(t_philo) * (num_philos));
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < num_philos)
	{
		philosophers[i].lock_print = malloc(sizeof(pthread_mutex_t));
		philosophers[i].lock_eat = malloc(sizeof(pthread_mutex_t));
		if (!philosophers[i].lock_print || !philosophers[i].lock_eat)
			return (NULL);
		philosophers[i].state = THINKING;
		philosophers[i].philosopher = i + 1;
		philosophers[i].meals_num = 0;
		philosophers[i].table = *table;
		philosophers[i].last_ate = now;
		i++;
	}
	return (philosophers);
}

int	parse_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
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
	t_philo	*philos;

	(*table)->lock_action = malloc(sizeof(pthread_mutex_t));
	(*table)->lock_death = malloc(sizeof(pthread_mutex_t));
	if (!(*table)->lock_action || !(*table)->lock_death)
		return (NULL);
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
	if (!(*table)->num_philos || !(*table)->to_die || !(*table)->to_eat
		|| !(*table)->to_sleep || !(*table)->rounds)
		return (NULL);
	philos = init_philos(table, (*table)->num_philos);
	return (philos);
}
