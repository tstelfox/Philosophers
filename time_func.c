/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/13 15:11:14 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/26 19:36:27 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_timestamp(t_philo *philo)
{
	struct timeval c_time;
	struct timeval s_time;
	
	long long	timestamp;

	gettimeofday(&c_time, NULL);
	s_time = philo->table->start_time;
	timestamp = (c_time.tv_sec - s_time.tv_sec) * 1000 
		+ (c_time.tv_usec - s_time.tv_usec) / 1000;
	return(timestamp);
}

bool	check_death(t_philo *philo)
{
	long long	difference;
	struct timeval	now;

	gettimeofday(&now, NULL);
	difference = (now.tv_sec - philo->last_ate.tv_sec) * 1000 
		+ (now.tv_usec - philo->last_ate.tv_usec) / 1000;
	if (difference >= philo->table->to_die)
		return (1);
	else
		return (0);
}

long long	get_diff(struct timeval now, t_philo *philo)
{
	long long difference;

	difference = (now.tv_sec - philo->table->start_time.tv_sec) * 
		1000 + (now.tv_usec - philo->table->start_time.tv_usec) / 1000;
	return (difference);
}

long int		get_usec(struct timeval start)
{
	struct timeval	current;
	long int		usec;

	gettimeofday(&current, NULL);
	usec = (current.tv_sec - start.tv_sec) * 1000000
		+ (current.tv_usec - start.tv_usec);
	return (usec);
}

void	precision_sleep(int duration, t_philo *philo)
{
	struct	timeval	start;

	(void)philo;
	gettimeofday(&start, NULL);
	while (get_usec(start) < duration * 1000) // && !any1dead
	{
		usleep(100);
	}
}
