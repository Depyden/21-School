/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 22:34:46 by depyden           #+#    #+#             */
/*   Updated: 2020/05/11 22:34:48 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*new_str;
	char	*new_cpy;

	if (!(new_str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	new_cpy = new_str;
	while (*s1 && size)
	{
		*new_cpy++ = *s1++;
		size--;
	}
	*new_cpy = '\0';
	return (new_str);
}
