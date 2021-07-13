/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:14:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/13 18:47:15 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

enum	states
{
	THINKING = 0,
	EATING = 1,
	SLEEPING = 2,
	DIED = 3
};

// typedef	struct	s_flags
// {
	// bool	full;
	// bool	dead;
// }				t_flags;

typedef	struct	s_table
{
	int	num_philos;
	pthread_mutex_t	*ch_stick;
	pthread_mutex_t	*lock_action;
	pthread_mutex_t *lock_death;
	// pthread_mutex_t *lock_print;
	struct timeval current_time;
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	struct timeval	start_time;
	bool	dinner_over;
	bool	sum1dead;
	unsigned int	rounds;
	/* data */
}				t_table;

typedef	struct	s_philo
{
	int	state;
	int	philosopher;
	bool	left;
	bool	right;
	int	meals_num;
	struct s_table	*table;
	long long	last_ate;
	
	/* data */
}				t_philo;

// Utils
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
unsigned long long	get_timestamp(t_philo *philo);

void		*thread_func(void *);
void		eat_loop(t_philo *philo);
void		print_action(t_philo *philo, int action);

#endif
