/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:21:46 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/12 22:11:49 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_map(int *tab, int length, int (*f)(int))
{
	int i;
	int *res;

	i = 0;
	res = (int*)malloc(length * sizeof(int));
	while (i < length)
	{
		res[i] = f(tab[i]);
		i++;
	}
	return (res);
}
