/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 20:03:44 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/27 20:08:59 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_philo *philo, t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philos)
	{
		free(philo[i].lock_print);
		free(philo[i].lock_eat);
		i++;
	}
	free(philo);
	free(table->lock_action);
	free(table->lock_death);
	free(table);
}
