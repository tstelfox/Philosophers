/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 20:36:29 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_func(void *arg)
{
	t_philo	*philo = arg;
	while (!philo->table->sum1dead)
	{
		pthread_mutex_lock(philo->table->lock_death);
		// pthread_mutex_lock(philo->table->lock_action);
		if (!philo->table->sum1dead)
		{
			if (check_death(philo))
			{
				print_action(philo, DIED);
			}
		}
		pthread_mutex_unlock(philo->table->lock_death);
		// pthread_mutex_unlock(philo->table->lock_action);
		// If dead lock everything and exit.
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
		// pthread_mutex_lock(philo->table->lock_action);
		if (philo->state == THINKING)
		eat_loop(philo);
		// pthread_mutex_unlock(philo->table->lock_action);
		sleep_or_think(philo);
		// if (philo->state == EATING)
		// {
		// }
		// if (philo->state == SLEEPING)
		// {
		// 	time_s = get_timestamp(philo);
		// 	printf("|%lld| Philosopher |%d| is thinking\n", time_s, philo->philosopher);
		// 	philo->state = THINKING;
		// }
	}
	return (NULL);
}
