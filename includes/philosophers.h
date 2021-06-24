/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:14:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/24 17:59:46 by tmullan       ########   odam.nl         */
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
	THINKING
};

typedef	struct	s_table
{
	int	num_philos;
	pthread_mutex_t	*ch_stick;
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_rest;
	// int	rounds;
	/* data */
}				t_table;

typedef	struct	s_philo
{
	// pthread_mutex_t	lock;
	int	philosopher;
	int	state;
	bool	left;
	bool	right;
	struct s_table	*table;
	/* data */
}				t_philo;



#endif
