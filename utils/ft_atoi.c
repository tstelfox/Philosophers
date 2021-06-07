/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 13:15:07 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/07 13:43:17 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		ft_conv(const char *str, int i, int sign)
{
	long int res;

	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			break ;
		if (res >= 922337203685477580)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}

int		ft_atoi(const char *str)
{
	int			i;
	long int	res;
	long int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_conv(str, i, sign));
}
