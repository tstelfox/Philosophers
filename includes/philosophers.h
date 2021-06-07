/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:14:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/07 13:44:29 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

// Utils
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);

enum	states
{
	EATING,
	THINKING,
	SLEEPING
};

typedef	struct	s_table
{
	int	philosopher;
	int	num_philos;
	// int	to_die;
	// int	to_eat;
	// int	to_rest;
	// int	rounds;
	/* data */
}				t_table;

typedef	struct	s_philo
{
	// pthread_mutex_t	lock;
	int	philosopher;
	/* data */
}				t_philo;



#endif
