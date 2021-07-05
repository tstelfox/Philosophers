/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 16:57:26 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/05 18:38:40 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_rekt(t_philo *philo, long long timestamp)
{
	printf("|%lld| Philosopher |%d| be ded\n", timestamp, philo->philosopher);
	exit(0);
}

unsigned long long	get_timestamp(t_philo *philo)
{
	struct timeval c_time;
	struct timeval s_time;
	
	long long	timestamp;

	gettimeofday(&c_time, NULL);
	s_time = philo->table->start_time;
	timestamp = (c_time.tv_sec - s_time.tv_sec) * 1000 + (c_time.tv_usec - s_time.tv_usec) / 1000;
	// printf("Time since last ate is |%lld|\n", timestamp - philo->last_ate);
	// printf("Time to die is |%d|\n", philo->table->to_die);
	if (timestamp - philo->last_ate > philo->table->to_die)
		get_rekt(philo, timestamp);
	// timestamp = 1000000 * c_time.tv_sec + c_time.tv_usec;
	// timestamp -= philo->table->start_time;
	// (void)philo;
	// timestamp = ((1000000 * (c_time.tv_sec - philo->table->current_time.tv_sec) + \
	// 	(c_time.tv_usec - philo->table->current_time.tv_usec)) / 1000);
	return(timestamp);
}

void	*thread_func(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	int	left = philo->philosopher - 1;
	int right = philo->philosopher;
	int	meal_count = 0;
	long long	time_s;

	if (philo->philosopher == philo->table->num_philos)
		right = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->table->ch_stick[left]);
		philo->left = true;
		pthread_mutex_lock(&philo->table->ch_stick[right]);
		philo->right = true;
		// if (!(philo->right && philo->left) && (philo->right || philo->left))
		// {
		// 	printf("IN HERE?\n");
		// 	if (philo->right)
		// 		pthread_mutex_unlock(&philo->table->ch_stick[right]);
		// 	else if(philo->left)
		// 		pthread_mutex_unlock(&philo->table->ch_stick[left]);
		// }
		// else
		// {
		meal_count++;
		time_s = get_timestamp(philo);
		philo->last_ate = time_s;
		printf("|%lld| Philosopher |%d| is eating\n", time_s, philo->philosopher);
		philo->state = EATING;
		usleep(philo->table->to_eat * 1000);
		philo->left = false;
		pthread_mutex_unlock(&philo->table->ch_stick[left]);
		philo->right = false;
		pthread_mutex_unlock(&philo->table->ch_stick[right]);
		// }
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
		if (meal_count == 10)
			break;
	}

	return (NULL);
}
