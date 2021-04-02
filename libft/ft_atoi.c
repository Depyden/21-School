/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 22:56:15 by lregenar          #+#    #+#             */
/*   Updated: 2020/05/12 17:50:10 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int s;
	int nbr;

	nbr = 0;
	s = 1;
	while (*str == '\t' || *str == '\v' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
	{
		s = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = 10 * nbr + (*str - '0');
		if (nbr < 0 && nbr != -2147483648)
			return (s == -1 ? 0 : -1);
		str++;
	}
	return (nbr * s);
}
