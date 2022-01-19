/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:23 by coder             #+#    #+#             */
/*   Updated: 2022/01/19 22:25:23 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int no_valid_input(char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	close(fd);
	if (fd == -1)
		return (write(2, "error\n", 6));
	if (!ft_strnstr(&argv[1][ft_strlen(argv[1]) - ft_strlen(".fdf")], ".fdf", ft_strlen(".fdf")))
		return (write(2, "error\n", 6));
	return (0);
}

void free_split(char **split)
{
	int i;

	i = 0;
	if (split == NULL)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


int change_camera_zdiv(int key, t_fdf *fdf)
{
	if (key == 78)
		fdf->map.camera.z_divisor *= 1.1;
	else if (key == 69 && (fdf->map.camera.z_divisor * 0.8 > 0))
		fdf->map.camera.z_divisor *= 0.8;
	if (key == 53)
		exit(0);
	rendering(fdf);
	return (0);
}

void set_camera(t_map *map_ptr)
{
	map_ptr->camera.zoom = min(WIDTH / (map_ptr->x_max) / 1.5, HEIGHT / (map_ptr->y_max) / 1.5);
	map_ptr->camera.z_divisor = 10;
}
/*
	the higher the resolution the higher the zoom
	the larger the map the lower the zoom
*/

void set_values(int y, char *line, t_map *map_ptr)
{
	int		x;
	char	**split_ptr;

	x = 0;
	split_ptr = ft_split(line, ' ');
	while (split_ptr[x])
	{
		if (x > map_ptr->x_max) {
			write(2, "error\n", 6);
			exit(0);
		}
		//don't i need to free here? even though "exit"?
		map_ptr->points[y][x].x = x;
		map_ptr->points[y][x].y = y;
		map_ptr->points[y][x].z = ft_atoi(split_ptr[x]);
		if (ft_strchr(split_ptr[x], 'x'))
			map_ptr->points[y][x].color = ft_hextoi(ft_strchr(split_ptr[x], 'x') + 1);
		else
			map_ptr->points[y][x].color = 0xffffff;
		// tt value missing, 0xttbbrrgg ???
		x++;
	}
	if (x != map_ptr->x_max)
	 {
		printf("x	%d\n x_max %d\n", x, map_ptr->x_max);
		write(2, "error\n", 6);
		exit(0);
	}
	free_split(split_ptr);
}

t_map set_map(char **argv)
{
	int   y;
	int   fd;
	char *line;
	t_map map;
	t_point **tmp;

	y = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	ft_bzero(&map, sizeof(t_map));
	map.x_max = ft_ptr_quantity(line, ' ');
	while (line)
	{
		tmp = ft_calloc(y + 2, sizeof(t_point *));
		ft_memcpy(tmp, map.points, sizeof(t_point *) * y);
		free(map.points);
		map.points = tmp;
		map.points[y] = ft_calloc(map.x_max + 1, sizeof(t_point));
		set_values(y, line, &map);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	map.y_max = y;
	set_camera(&map);
	return (map);
}
