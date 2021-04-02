/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <lregenar@student>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:47:41 by lregenar          #+#    #+#             */
/*   Updated: 2020/10/25 16:39:00 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_savecheck(char *arg, char *save)
{
	int	i;

	i = 0;
	while (arg[i] == save[i])
	{
		if (arg[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_namecheck(char *arg, char *text)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == text[2] && arg[i - 2] == text[1])
		&& (arg[i - 3] == text[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_mapcheck(t_all *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < s->map.y)
	{
		j = 0;
		while (j < s->map.x)
		{
			if (s->map.tab[i][j] != '1' && i == 0)
				return (-1);
			else if (s->map.tab[i][j] != '1' && i == s->map.y - 1)
				return (-2);
			else if (s->map.tab[i][j] != '1' && j == 0)
				return (-3);
			else if (s->map.tab[i][j] != '1' && j == s->map.x - 1)
				return (-4);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL || s->tex.i == NULL))
		return (ft_strerror(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (ft_strerror(-16));
	else if (s->err.p == 0)
		return (ft_strerror(-17));
	else if (s->err.p > 1)
		return (ft_strerror(-18));
	else if (ft_mapcheck(s) < 0)
		return (ft_strerror(-19));
	return (1);
}
