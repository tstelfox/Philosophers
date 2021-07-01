/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/01 17:44:25 by tmullan       ########   odam.nl         */
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
	while (1)
	{
		gettimeofday(&philo->table->current_time, NULL);
		printf("|%d| Philosopher |%d| starts thinking\n", philo->table->current_time.tv_usec - philo->table->start_time, philo->philosopher);
		usleep(philo->table->to_think);
		pthread_mutex_lock(&philo->table->ch_stick[left]);
		philo->left = true;
		pthread_mutex_unlock(&philo->table->ch_stick[left]);
		pthread_mutex_lock(&philo->table->ch_stick[right]);
		philo->right = true;
		pthread_mutex_unlock(&philo->table->ch_stick[right]);
		gettimeofday(&philo->table->current_time, NULL);
		if (philo->right && philo->left)
		{
			printf("|%d| Philosopher |%d| starts eating\n", philo->table->current_time.tv_usec - philo->table->start_time, philo->philosopher);
			philo->state = EATING;
			usleep(philo->table->to_eat);
			philo->left = false;
			philo->right = false;
			philo->state = THINKING;
			printf("Philosopher |%d| has finished eating\n", philo->philosopher);
		}
	}

	return (NULL);
}
