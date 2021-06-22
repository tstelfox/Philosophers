/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:14:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/22 16:50:55 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>

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

typedef	struct	s_philo
{
	// pthread_mutex_t	lock;
	int	philosopher;
	bool	left;
	bool	right;
	/* data */
}				t_philo;

typedef	struct	s_table
{
	int	philosopher;
	int	num_philos;
	pthread_mutex_t	*ch_stick;
	int	to_die;
	int	to_eat;
	int	to_rest;
	struct s_philo	*philo;
	// int	rounds;
	/* data */
}				t_table;


#endif
