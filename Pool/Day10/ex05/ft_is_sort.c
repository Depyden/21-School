/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 11:18:15 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/13 19:24:59 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int i;
	int up;
	int dwn;

	i = 1;
	up = 0;
	dwn = 0;
	if (length == 0 || length == 1)
		return (1);
	while (i < length)
	{
		if (f(tab[i - 1], tab[i]) >= 0)
			up++;
		if (f(tab[i - 1], tab[i]) <= 0)
			dwn++;
		i++;
	}
	if (up == length || dwn == length)
		return (1);
	else
		return (0);
}
