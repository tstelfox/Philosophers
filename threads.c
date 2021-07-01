/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/01 18:46:07 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;
	int	meal_count = 0;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	while (1)
	{
		gettimeofday(&philo->table->current_time, NULL);
		pthread_mutex_lock(&philo->table->ch_stick[left]);
		{
			philo->left = true;
		}
		pthread_mutex_unlock(&philo->table->ch_stick[left]);
		pthread_mutex_lock(&philo->table->ch_stick[right]);
		philo->right = true;
		pthread_mutex_unlock(&philo->table->ch_stick[right]);
		gettimeofday(&philo->table->current_time, NULL);
		if (philo->right && philo->left)
		{
			meal_count++;
			gettimeofday(&philo->table->current_time, NULL);
			printf("|%llu| Philosopher |%d| starts eating\n", (unsigned long long)philo->table->current_time.tv_usec - philo->table->start_time, philo->philosopher);
			philo->state = EATING;
			usleep(philo->table->to_eat);
			pthread_mutex_lock(&philo->table->ch_stick[left]);
			philo->left = true;
			pthread_mutex_unlock(&philo->table->ch_stick[left]);
			pthread_mutex_lock(&philo->table->ch_stick[right]);
			philo->right = false;
			pthread_mutex_unlock(&philo->table->ch_stick[right]);
			gettimeofday(&philo->table->current_time, NULL);
			printf("|%llu| Philosopher |%d| has finished eating\n", (unsigned long long)philo->table->current_time.tv_usec - philo->table->start_time, philo->philosopher);
		}
		if (philo->state == EATING)
		{
			printf("|%llu| Philosopher |%d| is sleeping\n", (unsigned long long)philo->table->current_time.tv_usec - philo->table->start_time, philo->philosopher);
			usleep(philo->table->to_sleep);
			philo->state = SLEEPING;
		}
		if (meal_count == 33)
			break;
	}

	return (NULL);
}
