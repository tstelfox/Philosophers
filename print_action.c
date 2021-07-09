/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 15:20:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/09 16:29:32 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo)
{
	long long	timestamp;

	pthread_mutex_lock(philo->table->lock_action);
	timestamp = get_timestamp(philo);
	if (philo->table->sum1dead)
	{
		philo->table->sum1dead = true;
		printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
	}
	else
	{
		(void)timestamp;
		// Other stuff
	}
	pthread_mutex_unlock(philo->table->lock_action);
}
