/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 15:20:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 15:54:41 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_action(t_philo *philo, int action)
{
	long long	timestamp;
	if (action == EATING)
	{
		timestamp = get_timestamp(philo);
		philo->last_ate = timestamp;
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
		// philo->table->sum1dead = true;
		printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
	}
	else
	{
		do_action(philo, action);
		// Other stuff
	}
	pthread_mutex_unlock(philo->table->lock_action);
}
