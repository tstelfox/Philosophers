/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 12:43:29 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/27 21:12:40 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grab_fork(pthread_mutex_t *ch_stick, t_philo *philo)
{
	pthread_mutex_lock(ch_stick);
	print_action(philo, GRAB);
}

void	drop_fork(pthread_mutex_t *ch_stick, t_philo *philo)
{
	pthread_mutex_unlock(ch_stick);
	print_action(philo, DROP);
}

void	eat_loop(t_philo *philo)
{
	int	left;
	int	right;

	right = philo->philosopher;
	left = philo->philosopher - 1;
	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	grab_fork(&philo->table->ch_stick[left], philo);
	grab_fork(&philo->table->ch_stick[right], philo);
	print_action(philo, EATING);
	precision_sleep(philo->table->to_eat, philo);
	philo->state = EATING;
	drop_fork(&philo->table->ch_stick[right], philo);
	drop_fork(&philo->table->ch_stick[left], philo);
}

void	sleep_or_think(t_philo *philo)
{
	if (philo->state == EATING)
	{
		print_action(philo, SLEEPING);
		precision_sleep(philo->table->to_sleep, philo);
		philo->state = SLEEPING;
	}
	if (philo->state == SLEEPING)
	{
		print_action(philo, THINKING);
		philo->state = THINKING;
	}	
}
