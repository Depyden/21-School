/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 23:15:52 by depyden           #+#    #+#             */
/*   Updated: 2020/05/12 17:54:27 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*block;

	if (!(block = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	block->content = content;
	block->next = NULL;
	return (block);
}
