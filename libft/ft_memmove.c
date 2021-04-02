/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:51:44 by depyden           #+#    #+#             */
/*   Updated: 2020/05/10 15:49:37 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL && len != 0)
		return (NULL);
	if ((src < dst) && (len != 0))
	{
		i = len;
		while (i > 0)
		{
			i--;
			((char *)dst)[i] = ((char*)src)[i];
		}
	}
	else if ((len != 0) && (src >= dst))
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}
