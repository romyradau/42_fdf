/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:39 by coder             #+#    #+#             */
/*   Updated: 2022/01/19 22:02:11 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

void draw_line(t_point start, t_point end, t_data *img)
{
	t_point	diff;
	t_point	direction;
	t_point	cursor;
	int		left_over[2];

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
	{
		my_mlx_pixel_put(img, cursor.x, cursor.y, cursor.color);
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
//watch a visual video for Bresenheim Algo!


void allBlack(t_fdf *fdf)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&fdf->img, x, y, 0x00000);
			x++;
		}
		y++;
	}
}

void rendering(t_fdf *fdf)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	allBlack(fdf);
	while (i < fdf->map.y_max)
	{
		j = 0;
		while (j < fdf->map.x_max)
		{
			if (j != fdf->map.x_max - 1)
				draw_line(dimensions(fdf->map.points[i][j], &fdf->map),
				          dimensions(fdf->map.points[i][j + 1], &fdf->map), &fdf->img);
			if (i != fdf->map.y_max - 1)
				draw_line(dimensions(fdf->map.points[i][j], &fdf->map),
				          dimensions(fdf->map.points[i + 1][j], &fdf->map), &fdf->img);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
}

int main(int argc, char **argv)
{
	t_fdf fdf;

	if (argc != 2 || no_valid_input(argv))
		exit(0);
	fdf.map = set_map(argv);
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "FreiheitDenFormen!");
	fdf.img.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bit_per_pixel,
	                                 &fdf.img.line_length, &fdf.img.endian);
	rendering(&fdf);
	mlx_key_hook(fdf.mlx_win, change_camera_zdiv, &fdf);
	mlx_loop(fdf.mlx);
	// do i need to free anything before loop can be closed?
}