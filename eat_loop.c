/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 12:43:29 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 15:53:48 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_loop(t_philo *philo)
{
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;
	// long long	time_s;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	pthread_mutex_lock(&philo->table->ch_stick[left]);
	pthread_mutex_lock(&philo->table->ch_stick[right]);
	print_action(philo, EATING);
	// pthread_mutex_lock(philo->table->lock_action);
	// timestamp = get_timestamp(philo);
	// philo->last_ate = time_s;
	// printf("|%lld| Philosopher |%d| is eating\n", time_s, philo->philosopher);
	// philo->state = EATING;
	// usleep(philo->table->to_eat * 1000);
	// pthread_mutex_unlock(philo->table->lock_action);
	pthread_mutex_unlock(&philo->table->ch_stick[left]);
	pthread_mutex_unlock(&philo->table->ch_stick[right]);
}
