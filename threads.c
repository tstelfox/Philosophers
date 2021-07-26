/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/26 19:33:41 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	any1dead(t_table *table)
{
	// int dead = 0;
	// pthread_mutex_lock(table->lock_death);
	// dead = table->sum1dead;
	// pthread_mutex_unlock(table->lock_death);
	return(table->sum1dead);
}

void	*monitor_func(void *arg)
{
	t_philo	*philo = arg;
	while (1)
	{
		pthread_mutex_lock(philo->table->lock_death);
		if (check_death(philo))
		{
			print_action(philo, DIED);
			pthread_mutex_unlock(philo->table->lock_death);
			return (NULL);
		}
		else if (any1dead(philo->table))
		{
			pthread_mutex_unlock(philo->table->lock_death);
			return (NULL);
		}
		pthread_mutex_unlock(philo->table->lock_death);
	}
	return(NULL);
}

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->table->num_philos == 1)
		return (NULL);
	if (philo->philosopher % 2)
		usleep(100);
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
