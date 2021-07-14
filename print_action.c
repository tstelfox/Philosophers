/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 15:20:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/14 18:13:35 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_action(t_philo *philo, int action)
{
	long long	timestamp;
	if (action == EATING)
	{
		timestamp = get_timestamp(philo);
		gettimeofday(&philo->last_ate, NULL);
		printf("|%lld| Philosopher |%d| is eating\n", timestamp, philo->philosopher);
		usleep(philo->table->to_eat * 1000);
	}
	else if (action == SLEEPING)
	{
		timestamp = get_timestamp(philo);
		printf("|%lld| Philosopher |%d| is sleeping\n", timestamp, philo->philosopher);
		usleep(philo->table->to_sleep * 1000);
	}
	else if (action == THINKING)
	{
		timestamp = get_timestamp(philo);
		printf("|%lld| Philosopher |%d| is thinking\n", timestamp, philo->philosopher);
	}
}

void	print_action(t_philo *philo, int action)
{
	long long	timestamp;

	pthread_mutex_lock(philo->lock_print);
	pthread_mutex_lock(philo->table->lock_action);
	if (action == DIED)
	{
		timestamp = get_timestamp(philo);
		printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
		philo->table->sum1dead = true;
	}
	else if (!any1dead(philo->table))
	{
		do_action(philo, action);
	}
	pthread_mutex_unlock(philo->table->lock_action);
	pthread_mutex_unlock(philo->lock_print);
}
