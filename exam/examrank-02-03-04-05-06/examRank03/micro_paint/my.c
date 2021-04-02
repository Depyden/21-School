#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_zone
{
	int		width;
	int		height;
	char	background;
}				t_zone;

typedef struct	s_list
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
}				t_list;

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (0);
}

int fail(char *error)
{
	write(1, error, ft_strlen(error));
	return (1);
}

int free_all(FILE *file, char *draw)
{
	fclose(file);
	if (draw)
		free(draw);
	return (1);
}

int	check_zone(t_zone *zone)
{
	return ((zone->width >= 0 && zone->width < 300) && (zone->height >= 0 && zone->height < 300));
}

int *get_zone(FILE *file, t_zone *zone)
{
	int count;
	char *array;
	int i;

	i = 0;
	if((count = fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3))
		return (NULL);
	if (!(check_zone(zone)))
		return(NULL);
	array = (char *)malloc(sizeof(char) * (zone->width * zone->height));
	while (i < zone->height * zone->width)
		array[i++] = zone->background;
	return (array);
}

int	check_tmp(t_list *tmp)
{
	return((tmp->height > 0.00000000 && tmp->width > 0.00000000) && (tmp->type == 'r' || tmp->type == 'R'));

}

void get_draw(char *draw, t_list *tmp, t_zone *zone)
{
	int x, y;
	int rec;

	y = 0;
	while(y < zone->height)
	{
		x = 0;
		while(x < zone->width)
		{
			rec = is_rec(y, x, tmp)
			if(())
		}
	}
}

int	drawing(FILE *file, char **draw, t_zone *zone)
{
	t_list tmp;
	int count;

	while ((count = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color)) == 6)
	{
		if(!(check_tmp(&tmp)))
			return (0);
		get_draw(draw, &tmp, zone);
	}
	if (count != -1)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	FILE *file;
	char *draw;
	t_zone zone;

	if (argc != 2)
		return(fail("Error argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return(fail("Error file\n"));
	if (!(draw = get_zone(file, &zone)))
		return(free_all(file, NULL) && fail("Error file\n"));
	if (!(drawing(file, &draw, &zone)))
		return(free_all(file, draw) && fail("Error file\n"));
	print_drawing(draw, &zone);
	free_all(file, draw);
	return (0);
}