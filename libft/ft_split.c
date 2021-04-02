/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: depyden <depyden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:33:49 by depyden           #+#    #+#             */
/*   Updated: 2020/05/11 19:19:43 by depyden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cr(const char *str, char c)
{
	int count;

	count = 0;
	if (*str != c && *str)
	{
		str++;
		count++;
	}
	while (*str)
	{
		while (*str == c)
		{
			str++;
			if (*str != c && *str)
				count++;
		}
		str++;
	}
	return (count);
}

static int	ft_cl(const char *str, char c)
{
	int count;

	count = 0;
	while (*str != c && *str)
	{
		count++;
		str++;
	}
	return (count);
}

static void	*is_free(char **spt)
{
	int		i;

	i = 0;
	while (spt[i])
	{
		free(spt[i++]);
	}
	free(spt);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**spt;

	i = 0;
	j = 0;
	if (!s || (!(spt = (char**)malloc(sizeof(char*) * (ft_cr(s, c) + 1)))))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			if (!(spt[j] = (char *)malloc(sizeof(char) * (ft_cl(s, c) + 1))))
				return (is_free(spt));
			while (*s && *s != c)
				spt[j][i++] = (char)*s++;
			spt[j][i] = '\0';
			j++;
			i = 0;
		}
	}
	spt[j] = NULL;
	return (spt);
}
