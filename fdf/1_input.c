/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:23 by coder             #+#    #+#             */
/*   Updated: 2021/12/26 11:46:46 by coder            ###   ########.fr       */
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


t_map	get_map_dimensions(char **argv)
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
	ft_bzero(&map, sizeof(map));
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
			exit(0) ;
			//ok program ur gone 4eva
		}
		map.x_max = x_coordinate(x_values);
			//do i need this line at all?
			//hier muss ich mir noch überlegen wei ich mit error umgehe
		map.y_max++;
		free(x_line);
		x_line = get_next_line(fd);
	}
	free_split(x_values);
	close(fd);
	return (map);
}
//map.points noch bestimmen aber wo?
void	set_camera(t_map *map_ptr)
{	
	map_ptr->camera.zoom = min(WIDTH / map_ptr->x_max / 2, HEIGHT / map_ptr->y_max / 2);
	map_ptr->camera.z_divisor = 1;
}

//why don't in need malloc here?

void	set_values(int	y, char	*line, t_map *map_ptr)
{
	int			x;
	char		**split_ptr;

	x = 0;
	split_ptr = ft_split(line, ' ');
		while (split_ptr[x])//stimmt das hier oder <= ??
		{
			map_ptr->points[y][x].x = x;
			map_ptr->points[y][x].y = y;
			map_ptr->points[y][x].z = ft_atoi(split_ptr[x]);
			if (ft_strchr(split_ptr[x], 'x'))
				map_ptr->points[y][x].color = ft_hextoi(ft_strchr(split_ptr[x], 'x') + 1);
			//pointer incrementen nochmal verstehen!
			else
				map_ptr->points[y][x].color = 0xffffff;
				//tt wert fehlt?
			x++;
		}
	free_split(split_ptr);
}

t_map	set_map(char **argv)
{
	int			y;
	int			fd;
	char		*line;
	t_map		map;

	map = get_map_dimensions(argv);
	map.points = malloc(sizeof(t_point*) * map.y_max);//pointer auf die y reihen
	//doublepointer braucht platz für y viele relief pointer
	y = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (y < map.y_max)
	//or y <= general explanation, im having such a hard time to get those +- 1shit
	{
		map.points[y] = malloc(sizeof(t_point) * (map.x_max + 1));
		//hier hat eine + 1 gefehlt aber warum - auf jeden Fall für '\0' ?!
		//printf("map[y]: %p\n", map.points[y]);
		//printf("x_max: %d\n", map.x_max);
		set_values(y, line, &map);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	set_camera(&map);
	return (map);
}