/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 16:22:19 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/07 17:55:52 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int z;

	z = 0;
	if (a && b)
	{
		z = *a;
		*a = *b;
		*b = z;
	}
}
