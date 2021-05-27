/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/27 17:19:12 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	process_args(char *argv[])
{
	/*
		Do the classic argument parsing.
		Store the arguments in a struct
	*/
	int	num_phil;

	num_phil = ft_atoi(argv[1]);
}

void	init_philos(char *argv[])
{
	/*
	pthread_t	philosopher[num_phil];
	*/
}

int	main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		process_args(argv);
		init_philos(argv);
		ft_putstr_fd(argv[4], 1);
	}
	else
	{
		ft_putstr_fd("Wrong no. of args\n", 1);
	}
	return (0);
}
