/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 18:21:53 by tmullan       #+#    #+#                 */
/*   Updated: 2021/07/27 18:22:18 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		ft_isdigit(int arg)
{
	if ((arg >= '0') && (arg <= '9'))
		return (1);
	else
		return (0);
}
