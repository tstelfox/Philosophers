/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 20:59:14 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_func(void *arg)
{
	t_philo	*philo = arg;
	while (!philo->table->sum1dead)
	{
		pthread_mutex_lock(philo->table->lock_death);
		if (!philo->table->sum1dead)
		{
			if (check_death(philo))
			{
				print_action(philo, DIED);
			}
		}
		pthread_mutex_unlock(philo->table->lock_death);
	}
	return(NULL);
}

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	pthread_t	monitor[philo->table->num_philos];
	int i;

	i = 0;
	while (i < philo->table->num_philos)
	{
		pthread_create(&monitor[i], NULL, &monitor_func, (void *)philo);
		i++;
	}
	while (!philo->table->sum1dead)
	{
		if (philo->state == THINKING)
		eat_loop(philo);
		sleep_or_think(philo);
	}
	return (NULL);
}
