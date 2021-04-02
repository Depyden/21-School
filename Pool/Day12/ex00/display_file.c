/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:11:14 by lregenar          #+#    #+#             */
/*   Updated: 2019/08/15 20:26:04 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int		print_file(char *name)
{
	int		fd;
	char	buf[1];

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Open ERROR\n", 11);
		return (1);
	}
	while (read(fd, buf, sizeof(buf)))
	{
		write(1, buf, sizeof(buf));
	}
	if (close(fd) == -1)
	{
		write(2, "Close ERROR\n", 12);
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int err;

	err = 0;
	if (argc == 2)
		err = print_file(argv[1]);
	else if (argc < 2)
		write(2, "File name missing.\n", 19);
	else
		write(2, "Too many arguments.\n", 20);
	if (err == 1)
		return (1);
	else
		return (0);
}
