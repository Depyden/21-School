/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckakuna <ck@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 12:55:10 by leweathe          #+#    #+#             */
/*   Updated: 2020/08/22 13:07:48 by ckakuna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

int			ft_strchr(const char *s)
{
	int		i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			i++;
		}
		if (s[i] == '|' || s[i] == ';' || s[i] == '\n')
			return (i);
	}
	return (i < 0 ? 0 : i);
}
