/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 12:43:29 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/15 12:22:40 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grab_fork(pthread_mutex_t *ch_stick, t_philo *philo, int number)
{
	pthread_mutex_lock(ch_stick);
	printf("|%lld| Philosopher |%d| grabs fork no. |%d|\n", get_timestamp(philo), 
			philo->philosopher, number);
}

void	drop_fork(pthread_mutex_t *ch_stick, t_philo *philo, int number)
{
	pthread_mutex_unlock(ch_stick);
	printf("|%lld| Philosopher |%d| drops fork no. |%d|\n", get_timestamp(philo), 
			philo->philosopher, number);
}

void	eat_loop(t_philo *philo)
{
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	
	grab_fork(&philo->table->ch_stick[left], philo, left);
	grab_fork(&philo->table->ch_stick[right], philo, right);

	print_action(philo, EATING);
	philo->state = EATING;

	drop_fork(&philo->table->ch_stick[left], philo, left);
	drop_fork(&philo->table->ch_stick[right], philo, right);
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
