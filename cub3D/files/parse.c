/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <lregenar@student>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:48:56 by lregenar          #+#    #+#             */
/*   Updated: 2020/10/16 00:02:05 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_special_spaceskip(line, &i);
	if ((line[i] == '1' || s->err.m == 1) && line[i] != '\0')
		s->err.n = ft_map(s, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		s->err.n = ft_res(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.c, line, &i);
	if (ft_special_spaceskip(line, &i) && s->err.n == 0 && line[i] != '\0')
		return (ft_strerror(-10));
	return (s->err.n < 0 ? ft_strerror(s->err.n) : 0);
}

int		get_next_line(int fd, char **line)
{
	int			read_size;
	char		buf[4096];
	static char	*stock = NULL;

	if (line == NULL || fd < 0)
		return (-2);
	*line = NULL;
	read_size = 1;
	while (!(newline_check(stock, read_size)))
	{
		if ((read_size = read(fd, buf, 4095)) == -1)
			return (-2);
		buf[read_size] = '\0';
		if ((stock = buf_join(stock, buf)) == NULL)
			return (-2);
	}
	if ((*line = get_line(stock)) == NULL)
		return (-2);
	if (read_size == 0)
		free(stock);
	if (read_size == 0)
		return (0);
	if ((stock = stock_trim(stock)) == NULL)
		return (-2);
	return (1);
}

int		ft_parse(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		return (ft_strerror(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ft_line(s, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1 || ret == -3)
		return (ft_strerror(ret + 1));
	ft_pos(s);
	s->spr = NULL;
	ft_slist(s);
	return (ft_parcheck(s));
}
