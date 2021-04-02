/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 01:28:58 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/16 02:24:09 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree		*btree_create_node(void *item)
{
	t_btree	*a;

	a = (t_btree*)malloc(sizeof(t_btree));
	a->left = 0;
	a->right = 0;
	a->item = item;
	return (a);
}
