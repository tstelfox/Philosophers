/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 12:43:29 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 22:49:55 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_loop(t_philo *philo)
{
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	pthread_mutex_lock(&philo->table->ch_stick[left]);
	pthread_mutex_lock(&philo->table->ch_stick[right]);

	print_action(philo, EATING);
	philo->state = EATING;

	pthread_mutex_unlock(&philo->table->ch_stick[left]);
	pthread_mutex_unlock(&philo->table->ch_stick[right]);
}

void	sleep_or_think(t_philo *philo)
{
	if (philo->state == EATING)
	{
		print_action(philo, SLEEPING);
		usleep(philo->table->to_sleep * 1000);
		philo->state = SLEEPING;
	}
	if (philo->state == SLEEPING)
	{
		print_action(philo, THINKING);
		philo->state = THINKING;
	}	
}
