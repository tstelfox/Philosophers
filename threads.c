/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/22 21:01:45 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	any1dead(t_table *table)
{
	return(table->sum1dead);
}

void	*monitor_func(void *arg)
{
	t_philo	*philo = arg;
	t_philo *current;
	current = philo;
	int i;
	while (1)
	{
		i = 0;
		while (i < current->table->num_philos)
		{
			// printf("Philosopher is |%d|\n", current->philosopher);
			current = &philo[i];
			pthread_mutex_lock(current->table->lock_death);
			if (!any1dead(current->table))
			{
				if (check_death(current))
				{
					print_action(current, DIED);
					pthread_mutex_unlock(current->table->lock_death);
					return (NULL);
				}
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
		usleep(100);
	while (1)
	{
		// printf("What\n");
		if (philo->state == THINKING)
			eat_loop(philo);
		sleep_or_think(philo);
		// pthread_mutex_lock(philo->table->lock_death);
		if (any1dead(philo->table))
		{
			pthread_mutex_unlock(philo->table->lock_death);
			return (NULL);
		}
		// pthread_mutex_unlock(philo->table->lock_death);
	}
	return (NULL);
}
