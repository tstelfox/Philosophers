/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 19:13:40 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	get_rekt(t_philo *philo)
// {
// 	// pthread_mutex_t	*lock;

// 	// lock = &philo->table->lock_action;
// 	// pthread_mutex_lock(philo->table->lock_action);
// 	print_action(philo);
// 	// printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
// 	// exit(0);
// 	// pthread_mutex_lock(philo->table->lock_action);
// }

void	*monitor_func(void *arg)
{
	t_philo	*philo = arg;
	while (!philo->table->sum1dead)
	{
		// print_action(philo);
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
	long long	time_s;
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
		if (philo->state == EATING)
		{
			time_s = get_timestamp(philo);
			printf("|%lld| Philosopher |%d| is sleeping\n", time_s, philo->philosopher);
			usleep(philo->table->to_sleep * 1000);
			philo->state = SLEEPING;
		}
		if (philo->state == SLEEPING)
		{
			time_s = get_timestamp(philo);
			printf("|%lld| Philosopher |%d| is thinking\n", time_s, philo->philosopher);
			philo->state = THINKING;
		}
	}
	return (NULL);
}
