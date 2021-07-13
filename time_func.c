/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/13 15:11:14 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 15:23:19 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	get_timestamp(t_philo *philo)
{
	struct timeval c_time;
	struct timeval s_time;
	
	long long	timestamp;

	gettimeofday(&c_time, NULL);
	s_time = philo->table->start_time;
	timestamp = (c_time.tv_sec - s_time.tv_sec) * 1000 + (c_time.tv_usec - s_time.tv_usec) / 1000;
	return(timestamp);
}
