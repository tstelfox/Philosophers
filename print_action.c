/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 15:20:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/14 19:16:34 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_action(t_philo *philo, int action, struct timeval action_time)
{
	long long	timestamp;
	if (action == EATING)
	{
		timestamp = get_diff(action_time, philo);
		gettimeofday(&philo->last_ate, NULL);
		printf("|%lld| Philosopher |%d| is eating\n", timestamp, philo->philosopher);
		precision_sleep(philo->table->to_eat, philo);
	}
	else if (action == SLEEPING)
	{
		timestamp = get_diff(action_time, philo);
		printf("|%lld| Philosopher |%d| is sleeping\n", timestamp, philo->philosopher);
		precision_sleep(philo->table->to_sleep, philo);
	}
	else if (action == THINKING)
	{
		timestamp = get_diff(action_time, philo);
		printf("|%lld| Philosopher |%d| is thinking\n", timestamp, philo->philosopher);
	}
}

void	print_action(t_philo *philo, int action)
{
	long long	timestamp;
	struct timeval	action_time;

	gettimeofday(&action_time, NULL);
	pthread_mutex_lock(philo->lock_print);
	pthread_mutex_lock(philo->table->lock_action);
	if (action == DIED)
	{
		timestamp = get_diff(action_time, philo);
		printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
		philo->table->sum1dead = true;
	}
	else if (!any1dead(philo->table))
	{
		do_action(philo, action, action_time);
	}
	pthread_mutex_unlock(philo->table->lock_action);
	pthread_mutex_unlock(philo->lock_print);
}
