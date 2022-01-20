/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:23 by coder             #+#    #+#             */
/*   Updated: 2022/01/20 22:00:51 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_camera(t_map *map_ptr)
{
	map_ptr->camera.zoom = min(WIDTH / (map_ptr->x_max) / 1.5,
			HEIGHT / (map_ptr->y_max) / 1.5);
	map_ptr->camera.z_divisor = 10;
}
/*
    the higher the resolution the higher the zoom
    the larger the map the lower the zoom
*/

void	set_values(int y, char *line, t_map *map_ptr)
{
	int		x;
	char	**split_ptr;

	x = 0;
	split_ptr = ft_split(line, ' ');
	while (split_ptr[x])
	{
		if (x > map_ptr->x_max)
			exec_failed("incorrect map");
		map_ptr->points[y][x].x = x;
		map_ptr->points[y][x].y = y;
		map_ptr->points[y][x].z = ft_atoi(split_ptr[x]);
		if (ft_strchr(split_ptr[x], 'x'))
			map_ptr->points[y][x].color
				= ft_hextoi(ft_strchr(split_ptr[x], 'x') + 1);
		else
			map_ptr->points[y][x].color = 0xffffff;
		x++;
	}
	if (x != map_ptr->x_max)
		exec_failed("incorrect map");
	free_split(split_ptr);
}

int	extend_map(char *line, t_map *map, int fd, int y)
{
	t_point	**tmp;

	while (line)
	{
		tmp = ft_calloc(y + 2, sizeof(t_point *));
		ft_memcpy(tmp, map->points, sizeof(t_point *) * y);
		free(map->points);
		map->points = tmp;
		map->points[y] = ft_calloc(map->x_max + 1, sizeof(t_point));
		set_values(y, line, map);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	return (y);
}

t_map	set_map(char **argv)
{
	int		y;
	int		fd;
	char	*line;
	t_map	map;

	y = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL || *line == '\0')
		exec_failed("empty map");
	ft_bzero(&map, sizeof(t_map));
	map.x_max = ft_ptr_quantity(line, ' ');
	y = extend_map(line, &map, fd, y);
	map.y_max = y;
	set_camera(&map);
	close(fd);
	return (map);
}
