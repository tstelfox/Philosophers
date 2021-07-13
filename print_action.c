/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 15:20:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 16:19:49 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_action(t_philo *philo, int action)
{
	long long	timestamp;
	if (action == EATING)
	{
		timestamp = get_timestamp(philo);
		pthread_mutex_lock(philo->table->lock_death);
		philo->last_ate = timestamp;
		pthread_mutex_unlock(philo->table->lock_death);
		printf("|%lld| Philosopher |%d| is eating\n", timestamp, philo->philosopher);
		usleep(philo->table->to_eat * 1000);
	}
}

void	print_action(t_philo *philo, int action)
{
	long long	timestamp;

	timestamp = get_timestamp(philo);
	pthread_mutex_lock(philo->table->lock_action);
	if (action == DIED)
	{
		philo->table->sum1dead = true;
		printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
	}
	else
	{
		do_action(philo, action);
		// Other stuff
	}
	pthread_mutex_unlock(philo->table->lock_action);
}

// pthread_mutex_lock(philo->table->lock_death);
// if (get_timestamp(philo) - philo->last_ate > philo->table->to_die)
// 	philo->table->sum1dead = true;
// pthread_mutex_unlock(philo->table->lock_death);