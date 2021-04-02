/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:08:51 by depyden           #+#    #+#             */
/*   Updated: 2020/05/11 19:16:20 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1 + start);
	if (end)
		while (s1[end + start - 1] != 0 && \
				ft_strchr(set, s1[end + start - 1]) != 0)
			end--;
	if (!(trim = malloc(sizeof(char) * end + 1)))
		return (NULL);
	ft_strncpy(trim, s1 + start, end);
	trim[end] = '\0';
	return (trim);
}
