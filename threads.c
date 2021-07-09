/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/09 15:44:28 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_rekt(t_philo *philo)
{
	// pthread_mutex_t	*lock;

	// lock = &philo->table->lock_action;
	// pthread_mutex_lock(philo->table->lock_action);
	philo->dead = true;
	print_action(philo);
	// printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
	// exit(0);
	// pthread_mutex_lock(philo->table->lock_action);
}

unsigned long long	get_timestamp(t_philo *philo)
{
	struct timeval c_time;
	struct timeval s_time;
	
	long long	timestamp;

	gettimeofday(&c_time, NULL);
	s_time = philo->table->start_time;
	timestamp = (c_time.tv_sec - s_time.tv_sec) * 1000 + (c_time.tv_usec - s_time.tv_usec) / 1000;
	pthread_mutex_lock(philo->table->lock_death);
	if (timestamp - philo->last_ate > philo->table->to_die)
	{
		philo->dead = true;
		// pthread_mutex_unlock(philo->table->lock_action);
		print_action(philo);
	}
	pthread_mutex_unlock(philo->table->lock_death);
	return(timestamp);
}

void	*monitor_func(void *arg)
{
	t_philo	*philo = arg;
	while (1)
	{
		if (philo->dead == true)
		{
			print_action(philo);
		}
		// If dead lock everything and exit.
	}
}

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	long long	time_s;
	pthread_t	monitor[philo->table->num_philos];
	int i;

	i = 0;
	while (i < philo->table->num_philos)
	{
		pthread_create(&monitor[i], NULL, &monitor_func, (void *)philo);
		i++;
	}
	while (!philo->table->sum1dead)
	{
		eat_loop(philo);
		if (philo->state == EATING)
		{
			time_s = get_timestamp(philo);
			printf("|%lld| Philosopher |%d| is sleeping\n", time_s, philo->philosopher);
			usleep(philo->table->to_sleep * 1000);
			philo->state = SLEEPING;
		}
		if (philo->state == SLEEPING)
		{
			time_s = get_timestamp(philo);
			printf("|%lld| Philosopher |%d| is thinking\n", time_s, philo->philosopher);
			philo->state = THINKING;
		}
	}

	return (NULL);
}
