/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:50:25 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/14 23:34:12 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list		*ft_list_last(t_list *begin_list)
{
	t_list *current;

	current = begin_list;
	if (begin_list)
	{
		while (current->next != 0)
			current = current->next;
	}
	return (current);
}
