/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <lregenar@student>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:14:44 by lregenar          #+#    #+#             */
/*   Updated: 2020/07/22 15:49:33 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	unsigned int	i;

	ch = (unsigned char)c;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == ch)
			return (char*)(s + i);
		i++;
	}
	if (ch == '\0' && s[i] == '\0')
		return (char*)(s + i);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	res_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(res_len * sizeof(char) + sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
