/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:35:32 by depyden           #+#    #+#             */
/*   Updated: 2020/05/13 16:28:23 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		if (!(sub = malloc(sizeof(char))))
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	else if (s && len >= 0)
	{
		return (ft_strndup(&s[start], len));
	}
	else
		return (NULL);
}
