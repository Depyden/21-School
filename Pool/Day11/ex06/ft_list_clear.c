/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 21:20:42 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/14 22:16:26 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_clear(t_list **begin_list)
{
	if (*begin_list && (*begin_list)->next)
	{
		ft_list_clear(&(*begin_list)->next);
	}
	free(*begin_list);
	*begin_list = 0;
}
