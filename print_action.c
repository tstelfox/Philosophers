/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 15:20:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/27 21:11:41 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_chop(t_philo *philo, int action)
{
	if (action == GRAB)
	{
		printf("|%lld| Philosopher |%d| grabs a chopstick\n",
			get_timestamp(philo), philo->philosopher);
	}
	else if (action == DROP)
	{
		printf("|%lld| Philosopher |%d| drops a chopstick\n",
			get_timestamp(philo), philo->philosopher);
	}
}

void	do_action(t_philo *philo, int action)
{
	if (action == EATING)
	{
		gettimeofday(&philo->last_ate, NULL);
		pthread_mutex_lock(philo->lock_eat);
		philo->meals_num++;
		pthread_mutex_unlock(philo->lock_eat);
		printf("|%lld| Philosopher |%d| is eating\n", get_timestamp(philo),
			philo->philosopher);
	}
	else if (action == SLEEPING)
	{
		printf("|%lld| Philosopher |%d| is sleeping\n", get_timestamp(philo),
			philo->philosopher);
	}
	else if (action == THINKING)
	{
		printf("|%lld| Philosopher |%d| is thinking\n", get_timestamp(philo),
			philo->philosopher);
	}
	print_chop(philo, action);
}

void	print_action(t_philo *philo, int action)
{
	long long		timestamp;
	struct timeval	action_time;

	gettimeofday(&action_time, NULL);
	pthread_mutex_lock(philo->table->lock_action);
	pthread_mutex_lock(philo->lock_print);
	if (action == DIED)
	{
		timestamp = get_timestamp(philo);
		printf("|%lld| Philosopher |%d| be ded\n", timestamp,
			philo->philosopher);
		philo->table->sum1dead = true;
	}
	if (action == FULL)
	{
		printf("Everybody has eaten their fill\n");
		philo->table->dinner_over = true;
	}
	else if (!any1dead(philo->table))
		do_action(philo, action);
	pthread_mutex_unlock(philo->lock_print);
	pthread_mutex_unlock(philo->table->lock_action);
}
