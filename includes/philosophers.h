/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:14:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/27 17:19:22 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

// Utils
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);

#endif
