/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:14:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/27 22:06:55 by tmullan       ########   odam.nl         */
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

enum	e_states
{
	THINKING = 0,
	EATING = 1,
	SLEEPING = 2,
	DIED = 3,
	GRAB = 4,
	DROP = 5,
	FULL = 6
};

typedef struct s_table
{
	int				num_philos;
	pthread_mutex_t	*ch_stick;
	pthread_mutex_t	*lock_action;
	pthread_mutex_t	*lock_death;
	struct timeval	current_time;
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	struct timeval	start_time;
	bool			dinner_over;
	bool			sum1dead;
	int				rounds;
}				t_table;

typedef struct s_philo
{
	pthread_mutex_t	*lock_print;
	pthread_mutex_t	*lock_eat;
	int				state;
	int				philosopher;
	bool			left;
	bool			right;
	int				meals_num;
	struct s_table	*table;
	struct timeval	last_ate;
}				t_philo;

// Utils
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
long long	get_timestamp(t_philo *philo);
int			ft_isdigit(int arg);

void		*thread_func(void *arg);
void		eat_loop(t_philo *philo);
void		print_action(t_philo *philo, int action);
bool		check_death(t_philo *philo);
void		sleep_or_think(t_philo *philo);
void		*monitor_func(t_philo *philo);
bool		any1dead(t_table *table);
void		precision_sleep(int duration, t_philo *philo);
long long	get_diff(struct timeval now, t_philo *philo);
void		free_all(t_philo *philo, t_table *table);
t_philo		*process_args(int argc, char *argv[], t_table **table);
#endif
