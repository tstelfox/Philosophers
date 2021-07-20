/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 12:43:29 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/20 17:18:41 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grab_fork(pthread_mutex_t *ch_stick, t_philo *philo)
{
	pthread_mutex_lock(ch_stick);
	print_action(philo, GRAB);
	// philo->table->other_cs = true;
}

void	drop_fork(pthread_mutex_t *ch_stick, t_philo *philo)
{
	pthread_mutex_unlock(ch_stick);
	print_action(philo, DROP);
}

void	eat_loop(t_philo *philo)
{
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	if (philo->philosopher % 2)
	{
		grab_fork(&philo->table->ch_stick[right], philo);
		grab_fork(&philo->table->ch_stick[left], philo);
	}
	else
	{
		grab_fork(&philo->table->ch_stick[left], philo);
		grab_fork(&philo->table->ch_stick[right], philo);
	}
	// printf("Who is stuck here? |philo %d|\n", philo->philosopher);

	// philo->table->other_cs = false;
	print_action(philo, EATING);
	precision_sleep(philo->table->to_eat, philo);
	philo->state = EATING;
	if (philo->philosopher % 2)
	{
		drop_fork(&philo->table->ch_stick[left], philo);
		drop_fork(&philo->table->ch_stick[right], philo);
	}
	else
	{
		drop_fork(&philo->table->ch_stick[right], philo);
		drop_fork(&philo->table->ch_stick[left], philo);
	}
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
