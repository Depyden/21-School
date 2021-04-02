/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:24:02 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/14 18:13:23 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list *current;

	if (begin_list)
	{
		if (*begin_list == 0)
			*begin_list = ft_create_elem(data);
		else
		{
			current = ft_create_elem(data);
			current->next = *begin_list;
			*begin_list = current;
		}
	}
}
