/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:39 by coder             #+#    #+#             */
/*   Updated: 2021/12/26 13:20:34 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
 	{
		printf("%d %d\n", x, y);
		dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	draw_line(t_point start, t_point end, t_data *img)
//had to remove the image pointer here
{
	t_point	diff;
	t_point	direction;
	t_point	cursor;
	int			left_over[2];
	
	diff.x = abs(start.x - end.x);
	diff.y = abs(start.y - end.y);
	if (start.x < end.x)
		direction.x = 1;
	else
		direction.x = -1;
	if (start.y < end.y)
		direction.y = 1;
	else
		direction.y = -1;
	cursor = start;
	left_over[0] = diff.x - diff.y;
	
	while (cursor.x != end.x || cursor.y != end.y) 
	//is this for checking which wall will be hit first?
	{
		my_mlx_pixel_put(img, cursor.x, cursor.y, cursor.color);
		//add the actual map.color!!!!!
		left_over[1] = left_over[0] * 2;
		if (left_over[1] > -diff.y)
		{
			left_over[0] -= diff.y;
			cursor.x += direction.x;
		}
		if (left_over[1] < diff.x)
		{
			left_over[0] += diff.x;
			cursor.y += direction.y;
		}
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		i;
	int		j;
	t_map	map;

	if (argc != 2 || no_valid_input(argv))
		exit(0);
	map = set_map(argv); 
	/*i = 0;
	while(i < map.y_max)
	{
		j = 0;
		while (j < map.x_max)
		{
			//printf("X: %d ",map.points[i][j].x);
			//printf("Y: %d ",map.points[i][j].y);
			if (map.points[i][j].z > 0)
			{
				
				printf("%d ",map.points[i][j].z);
				//printf("%d ",map.points[i][j].color);
			}
			else
			{
				printf(" %d ",map.points[i][j].z);
				//printf("%d ",map.points[i][j].color);
			}
			if (map.points[i][j].color != 0xffffff)
				printf("%d ",map.points[i][j].color);

			//printf("C: %d	",map.points[i][j].color);
			j++;	
		}
		i++;
		printf("\n");
	}
	*/
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello World!");
	(void) mlx_win;
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, 
	&img.bit_per_pixel, &img.line_length, &img.endian);
	/*
	t_point	A = {
		.x = 50, .y = 600
	};
	t_point	B = {
		.x = 80, .y = 800
	};
	*/
	//draw_line(A, B, &img);
	i = 0;
	while (i < map.y_max)
	//can structs be NULL?
	//but that aint right here, i mean i wann connect all the points 
	//of the whole map
	{
		j = 0;
		while (j < map.x_max)
		{
			if (j != map.x_max - 1)
    		draw_line(
        	dimensions(map.points[i][j], &map),
        	dimensions(map.points[i][j + 1], &map),
        	&img
    		);

			if (i != map.y_max - 1)
    		draw_line(
        	dimensions(map.points[i][j], &map),
        	dimensions(map.points[i + 1][j], &map),
        	&img
    		);
			j++;
		}
		//does it go from one poin to the next and so on and so on?
		//bu still how can the actual map be there than?
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx); // need stuff to end function (free etc)
}

