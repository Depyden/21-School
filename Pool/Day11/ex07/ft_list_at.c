/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 22:34:38 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/14 23:34:09 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list				*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	t_list			*current;
	unsigned int	i;

	i = 0;
	current = begin_list;
	if (begin_list)
	{
		while (current->next != 0)
		{
			if (i == nbr)
				return (current);
			i++;
			current = current->next;
		}
	}
	return (NULL);
}
