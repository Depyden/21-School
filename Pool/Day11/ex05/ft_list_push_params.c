/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:16:19 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/14 21:18:55 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void		ft_add(t_list **begin_list, void *data)
{
	t_list	*current;

	if (*begin_list == 0)
		*begin_list = ft_create_elem(data);
	else
	{
		current = ft_create_elem(data);
		current->next = *begin_list;
		*begin_list = current;
	}
}

t_list		*ft_list_push_params(int ac, char **av)
{
	int		i;
	t_list	*current;

	i = 0;
	current = 0;
	while (i < ac)
	{
		ft_add(&current, av[i]);
		i++;
	}
	return (current);
}
