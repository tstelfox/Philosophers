/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 15:20:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/26 19:28:23 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_action(t_philo *philo, int action)
{
	long long	timestamp;
	// pthread_mutex_lock(philo->lock_print);
	if (action == EATING)
	{
		timestamp = get_timestamp(philo);
		gettimeofday(&philo->last_ate, NULL);
		printf("|%lld| Philosopher |%d| is eating\n", timestamp, philo->philosopher);
	}
	else if (action == SLEEPING)
	{
		timestamp = get_timestamp(philo);
		printf("|%lld| Philosopher |%d| is sleeping\n", timestamp, philo->philosopher);
	}
	else if (action == THINKING)
	{
		timestamp = get_timestamp(philo);
		printf("|%lld| Philosopher |%d| is thinking\n", timestamp, philo->philosopher);
	}
	else if (action == GRAB)
	{
		printf("|%lld| Philosopher |%d| grabs a chopstick\n", get_timestamp(philo), 
			philo->philosopher);
	}
	else if (action == DROP)
	{
		printf("|%lld| Philosopher |%d| drops a chopstick\n", get_timestamp(philo), 
			philo->philosopher);
	}
	// pthread_mutex_unlock(philo->lock_print);
}

void	print_action(t_philo *philo, int action)
{
	long long	timestamp;
	struct timeval	action_time;

	gettimeofday(&action_time, NULL);
	pthread_mutex_lock(philo->table->lock_action);
		pthread_mutex_lock(philo->lock_print);
	if (action == DIED)
	{
		timestamp = get_timestamp(philo);
		printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
		// pthread_mutex_lock(philo->table->lock_death);
		philo->table->sum1dead = true;
		// pthread_mutex_unlock(philo->table->lock_death);
	}
	else if (!any1dead(philo->table))
		do_action(philo, action);
	pthread_mutex_unlock(philo->lock_print);
	pthread_mutex_unlock(philo->table->lock_action);
}
