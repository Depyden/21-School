/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 00:23:17 by depyden           #+#    #+#             */
/*   Updated: 2020/05/06 12:43:31 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	get_size(long n)
{
	unsigned int	size;

	size = 0;
	if (n == -2147483648)
		return (10);
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

char			*ft_itoa(int n)
{
	char			*str;
	unsigned int	size;
	unsigned int	i;
	long int		nb;

	i = 0;
	size = get_size(n);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1 + (n < 0 ? 1 : 0)))))
		return (NULL);
	nb = n;
	if (n < 0)
	{
		str[i] = '-';
		size++;
		nb = nb * (-1);
	}
	i = size - 1;
	while (nb >= 10)
	{
		str[i--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	str[i] = (char)(nb % 10 + 48);
	str[size] = '\0';
	return (str);
}
