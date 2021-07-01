/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/01 16:57:48 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	pthread_mutex_lock(&philo->table->ch_stick[left]);
	pthread_mutex_lock(&philo->table->ch_stick[right]);
	philo[philo->philosopher].left = true;
	philo[philo->philosopher].right = true;
	pthread_mutex_unlock(&philo->table->ch_stick[left]);
	pthread_mutex_unlock(&philo->table->ch_stick[right]);
	if (philo[philo->philosopher].left&& philo[philo->philosopher].right)
	{
		printf("Philosopher |%d| starts eating\n", philo->philosopher);
		philo->state = EATING;
		usleep(philo->table->to_eat);
		printf("Philosopher |%d| has finished eating\n", philo->philosopher);
		pthread_mutex_lock(&philo->table->ch_stick[left]);
		pthread_mutex_lock(&philo->table->ch_stick[right]);
		philo[philo->philosopher].left = false;
		philo[philo->philosopher].right = false;
		pthread_mutex_unlock(&philo->table->ch_stick[left]);
		pthread_mutex_unlock(&philo->table->ch_stick[right]);
	}
	else
	{
		philo->state = THINKING;
		usleep(philo->table->to_think);
	}

	return (NULL);
}
