/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:23 by coder             #+#    #+#             */
/*   Updated: 2021/12/15 18:10:52 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	no_valid_input(char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	close(fd);
	if (fd == -1)
		return (write(2, "error\n", 6));
	if (!ft_strnstr(&argv[1][ft_strlen(argv[1]) - ft_strlen(".fdf")], ".fdf", ft_strlen(".fdf")))
		return (write(2, "error\n", 6));
	return (0);
}

int	x_coordinate(char **line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (i);
	while (line[i] != NULL && *line[i] != '\n')
	{
		i++;
	}
	return (i);
}
void	free_split(char **split)
{
	int i;

	i = 0;
	if (split == NULL)
		return ;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	//geht weil man einem void pointer alles geben kann
}

int		ft_hextoi(char	*str)
{
	int		base;
	char	*hex;
	int		col;

	hex = "0123456789ABCDEF";
	base = 16;
	col = 0;
	while (*str != '\0')
	{
		col = col * base + (ft_strchr(hex, *str) - hex);
		//in dem man mit base multipliziert, shiftet man die breits bestehenden Zahlen nach links
		//mit der Basis multiplizieren für ein extra Feld
		str++;
	}
	return (col);
}

void	set_values(int	y, char	*line, t_map *map_ptr)
{
	int			x;
	char		**split_ptr;

	x = 0;
	split_ptr = ft_split(line, ' ');
		while (split_ptr[x])//stimmt das hier oder <= ??
		{
			map_ptr->cartography[y][x].x = x;
			map_ptr->cartography[y][x].y = y;
			map_ptr->cartography[y][x].z = ft_atoi(split_ptr[x]);
			if (ft_strchr(split_ptr[x], 'x'))
				map_ptr->cartography[y][x].color = ft_hextoi(ft_strchr(split_ptr[x], 'x') + 1);
			//pointer incrementen nochmal verstehen!
			else
				map_ptr->cartography[y][x].color = 0xffffff;
				//tt wert fehlt?
			x++;
		}
	free_split(split_ptr);
}


t_map	get_relief(char **argv)
{
	int			y;
	int			fd;
	char		*line;
	t_map		map;

	map = get_x_y_coordinates(argv);
	map.cartography = malloc(sizeof(t_relief*) * map.y_max);//pointer auf die y reihen
	//doublepointer braucht platz für y viele relief pointer
	y = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (y < map.y_max)
	{
		map.cartography[y] = malloc(sizeof(t_relief) * (map.x_max + 1));
		//hier hat eine + 1 gefehlt aber warum - auf jeden Fall für '\0'
		//printf("map[y]: %p\n", map.cartography[y]);
		//printf("x_max: %d\n", map.x_max);
		set_values(y, line, &map);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	return (map);
}

t_map	get_x_y_coordinates(char **argv)
{
	t_map	map;
	int		fd;
	//int		i;
	char	*x_line;
	char	**x_values;


	fd = open(argv[1], O_RDONLY);
	//i = 0;
	x_line = get_next_line(fd);
	x_values = ft_split(x_line, ' ');//double P auf NULL
	map.x_max = x_coordinate(x_values);
	map.y_max = 0;
	//free
	while (x_line) //error handling leere map - incomplete
	{
		free_split(x_values);
		x_values = ft_split(x_line, ' ');
		if (map.x_max != x_coordinate(x_values))
		{
			write(2, "error\n", 6);
			//muss nicht mal line freen weil stack?
			exit(0) ;
		}
		map.x_max = x_coordinate(x_values);
			//hier muss ich mir noch überlegen wei ich mit error umgehe
		map.y_max++;
		free(x_line);
		x_line = get_next_line(fd);
	}
	free_split(x_values);
	close(fd);
	return (map);
}
//map.cartography noch bestimmen aber wo?