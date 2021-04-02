/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <lregenar@student>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:19:49 by lregenar          #+#    #+#             */
/*   Updated: 2020/07/22 12:38:30 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	f;

	if (!s)
		return (NULL);
	i = 0;
	f = 0;
	while (i < start && s[i] != '\0')
		i++;
	if (!(res = malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	while ((f < len) && s[i + f] != '\0')
	{
		res[f] = s[i + f];
		f++;
	}
	res[f] = '\0';
	return (res);
}

int			fill_buff(int fd, char **my_line, char *buff, char **line)
{
	int		result;
	char	*temp;

	while ((result = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[result] = '\0';
		if (!my_line[fd])
			my_line[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(my_line[fd], buff);
			free(my_line[fd]);
			my_line[fd] = temp;
		}
		if (!my_line[fd])
			return (-1);
		if (ft_strchr(my_line[fd], '\n'))
			break ;
	}
	if (result == 0 && !(my_line[fd]))
		*line = ft_strdup("");
	return (result);
}

int			final_check(char **my_line, int fd, char **line, int reading_result)
{
	int		len;
	char	*temp;

	len = 0;
	while (my_line[fd][len] != '\n' && my_line[fd][len] != '\0')
		len++;
	if (my_line[fd][len] == '\n')
	{
		*line = ft_substr(my_line[fd], 0, len);
		temp = ft_strdup(my_line[fd] + len + 1);
		free(my_line[fd]);
		my_line[fd] = temp;
	}
	else if (my_line[fd][len] == '\0')
	{
		*line = ft_strdup(my_line[fd]);
		free(my_line[fd]);
		my_line[fd] = NULL;
	}
	if (reading_result == 0 && my_line[fd] == 0)
		return (0);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char *my_line[RLIMIT_NOFILE];
	char		*buff;
	int			reading_result;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || fd >= RLIMIT_NOFILE)
		return (-1);
	reading_result = 1;
	if (!ft_strchr(my_line[fd], '\n'))
	{
		if (!(buff = (char*)malloc(sizeof(*buff) * BUFFER_SIZE + 1)))
			return (-1);
		reading_result = fill_buff(fd, my_line, buff, line);
		free(buff);
	}
	else
		return (final_check(my_line, fd, line, reading_result));
	if (reading_result == 0 && my_line[fd] == 0)
		return (0);
	else if (reading_result < 0)
		return (-1);
	else
		return (final_check(my_line, fd, line, reading_result));
}
