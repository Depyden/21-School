/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:46:37 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/14 18:14:02 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int		ft_list_size(t_list *begin_list)
{
	int		i;
	t_list	*current;

	i = 0;
	if (begin_list)
	{
		current = begin_list;
		while (current)
		{
			current = current->next;
			i++;
		}
	}
	return (i);
}
