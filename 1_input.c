/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:23 by coder             #+#    #+#             */
/*   Updated: 2022/01/17 22:17:38 by rschleic         ###   ########.fr       */
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
	// geht weil man einem void pointer alles geben kann
}

t_map get_map_dimensions(char **argv)
{
	t_map map;
	int   fd;
	// int		i;
	char * x_line;
	char **x_values;

	printf("getting max value\n");
	fd = open(argv[1], O_RDONLY);
	// i = 0;
	x_line = get_next_line(fd);
	x_values = ft_split(x_line, ' '); // double P auf NULL
	ft_bzero(&map, sizeof(map));
	map.x_max = x_coordinate(x_values);
	map.y_max = 0;
	// free
	printf("getting max value in loop\n");
	while (x_line) // error handling leere map - incomplete
	{
		// free_split(x_values);
		// x_values = ft_split(x_line, ' ');
		if (map.x_max != x_coordinate(x_values))
		{
			write(2, "error\n", 6);
			exit(0);
			// ok program ur gone 4eva
		}
		//map.x_max = x_coordinate(x_values);
		// do i need this line at all???
		map.y_max++;
		free(x_line);
		x_line = get_next_line(fd);
	}
	//z_max_diff built in missing!
	printf("setting max value\n");
	// here its to slow
	free_split(x_values);
	close(fd);
	return (map);
}

int change_camera_zdiv(int key, t_fdf *fdf)
{
	if (key == 65451)
		fdf->map.camera.z_divisor *= 1.1;
	else if (key == 65453 && (fdf->map.camera.z_divisor * 0.8 > 0))
		fdf->map.camera.z_divisor *= 0.8;
	//does this really make sense... for the -= , it kinda makes the map weird
	if (key == 65307)
		exit(0);
	rendering(fdf);
	return (0);
}
// map.points noch bestimmen aber wo?
void set_camera(t_map *map_ptr)
{
	map_ptr->camera.zoom = min(WIDTH / (map_ptr->x_max) / 1.5, HEIGHT / (map_ptr->y_max) / 1.5);
	//do i need to change this for Julia?
	map_ptr->camera.z_divisor = 10;
	// missing a value that makes all maps visible
	// keyhook altitude change mit +/-
}

// why don't in need malloc here?

void set_values(int y, char *line, t_map *map_ptr)
{
	int    x;
	char **split_ptr;

	x = 0;
	split_ptr = ft_split(line, ' ');
	while (split_ptr[x]) // stimmt das hier oder <= ??
	{
		if (x > map_ptr->x_max) {
			write(2, "error\n", 6);
			exit(0);
		}
		//don't i need to free here already? even though "exit"?
		map_ptr->points[y][x].x = x;
		map_ptr->points[y][x].y = y;
		map_ptr->points[y][x].z = ft_atoi(split_ptr[x]);
		if (ft_strchr(split_ptr[x], 'x'))
			map_ptr->points[y][x].color = ft_hextoi(ft_strchr(split_ptr[x], 'x') + 1);
		// pointer incrementen nochmal verstehen!
		else
			map_ptr->points[y][x].color = 0xffffff;
		// tt wert fehlt?
		x++;
	}
	if (x != map_ptr->x_max)
	//fixed it cause x_max was 1 to much due to the +1 prev
	 {
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
	//pointer to a single struct

	y = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	ft_bzero(&map, sizeof(t_map));
	map.x_max = ft_ptr_quantity(line, ' ');
	// x_max = count amount of spaces
	while (line)
	// or y <= general explanation, im having such a hard time to get those +- 1shit
	{
		tmp = ft_calloc(y + 2, sizeof(t_point *));
		//had to change the syntax here
		ft_memcpy(tmp, map.points, sizeof(t_point *) * y);
		free(map.points);
		map.points = tmp;
		
		map.points[y] = ft_calloc(map.x_max + 1, sizeof(t_point));
		// hier hat eine + 1 gefehlt aber warum - auf jeden Fall für '\0' ?!
		// printf("map[y]: %p\n", map.points[y]);
		// printf("x_max: %d\n", map.x_max);
		set_values(y, line, &map);
		free(line);
		line = get_next_line(fd);
		y++;
	}

	map.y_max = y;
	
	// printf("y_max = %d, x_max = %d\n", map.y_max, map.x_max);
	// for (int i = 0; i < map.y_max; i++) {
	// 	for (int j = 0; j < map.x_max; j++) {
	// 		printf("%2d ", map.points[i][j].z);
	// 	}
	// 	
	// 	printf("\n");
	// }
	
	// map.points = NULL
	// tmp = undefined
	
	// tmp = allocation #1 -> 2 t_points
	// copy 0 from map.points to tmp
	// free map.points
	// set map.points to tmp
	
	// map.points = allocation #1 -> 2 t_points
	// tmp = allocation #2 -> 3 t_points
	// copy 1 from map.points to tmp
	// free map.points
	// set map.points to tmp
	write(1, "hallo\n", 6);
	set_camera(&map);
	return (map);
}