/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/27 18:42:58 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	any1dead(t_table *table)
{
	return(table->sum1dead || table->dinner_over);
}

bool	check_full(t_philo *philo)
{
	int i;
	t_philo *current;

	current = philo;
	i = 0;
	while (i < current->table->num_philos)
	{
		current = &philo[i];
		pthread_mutex_lock(current->lock_eat);
		if (current->meals_num != current->table->rounds)
		{
			pthread_mutex_unlock(current->lock_eat);
			break ;
		}
		pthread_mutex_unlock(current->lock_eat);
		i++;
		if (i == current->table->num_philos)
			return (true);
	}
	return (false);	
}

void	*monitor_func(t_philo *philo)
{
	int i;
	t_philo *current;

	current = philo;
	i = 0;
	while (1)
	{
		i = 0;
		usleep(100);
		while (i < current->table->num_philos)
		{
			current = &philo[i];
			pthread_mutex_lock(current->table->lock_death);
			if (check_death(current))
			{
				print_action(current, DIED);
				pthread_mutex_unlock(current->table->lock_death);
				return (NULL);
			}
			if (check_full(philo))
			{
				print_action(current, FULL);
				pthread_mutex_unlock(current->table->lock_death);
				return (NULL);
			}
			else if (any1dead(current->table))
			{
				pthread_mutex_unlock(current->table->lock_death);
				return (NULL);
			}
			pthread_mutex_unlock(current->table->lock_death);
			i++;
		}
	}
	return(NULL);
}

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->table->num_philos == 1)
		return (NULL);
	if (philo->philosopher % 2)
		usleep(200);
	while (1)
	{
		if (philo->state == THINKING)
			eat_loop(philo);
		sleep_or_think(philo);
		pthread_mutex_lock(philo->table->lock_death);
		if (any1dead(philo->table))
		{
			pthread_mutex_unlock(philo->table->lock_death);
			return (NULL);
		}
		pthread_mutex_unlock(philo->table->lock_death);
	}
	return (NULL);
}
