/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/31 18:50:25 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	any1dead(t_table *table)
{
	return (table->sum1dead || table->dinner_over);
}

bool	check_full(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->table->num_philos)
	{
		pthread_mutex_lock(philo[i].lock_eat);
		if ((philo[i].meals_num != philo->table->rounds) && !philo[i].full)
		{
			pthread_mutex_unlock(philo[i].lock_eat);
			break ;
		}
		philo[i].full = true;
		pthread_mutex_unlock(philo[i].lock_eat);
		i++;
		if (i == philo->table->num_philos)
			return (true);
	}
	return (false);
}

bool	we_done(t_philo *philo, int i)
{
	t_philo	*current;

	current = &philo[i];
	if (check_death(current))
	{
		print_action(current, DIED);
		pthread_mutex_unlock(current->table->lock_death);
		return (true);
	}
	if (philo->table->rounds != -1)
	{
		if (check_full(philo))
		{
			print_action(current, FULL);
			pthread_mutex_unlock(current->table->lock_death);
			return (true);
		}
	}
	return (false);
}

void	*monitor_func(t_philo *philo)
{
	int		i;
	t_philo	*current;

	current = philo;
	i = 0;
	while (1)
	{
		usleep(100);
		current = &philo[i];
		pthread_mutex_lock(current->table->lock_death);
		if (we_done(philo, i))
			return (NULL);
		else if (any1dead(current->table))
		{
			pthread_mutex_unlock(current->table->lock_death);
			return (NULL);
		}
		pthread_mutex_unlock(current->table->lock_death);
		i++;
		if (i == current->table->num_philos)
			i = 0;
	}
	return (NULL);
}

void	*thread_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->table->num_philos == 1)
		return (NULL);
	if (philo->philosopher % 2)
		usleep(300);
	while (1)
	{
		if (philo->state == THINKING)
			eat_loop(philo);
		sleep_or_think(philo);
		pthread_mutex_lock(philo->table->lock_death);
		if (any1dead(philo->table))
		{
			pthread_mutex_unlock(philo->table->lock_death);
			return (NULL);
		}
		pthread_mutex_unlock(philo->table->lock_death);
	}
	return (NULL);
}
