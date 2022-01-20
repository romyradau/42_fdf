/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:42:03 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/20 21:26:42 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bit_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

void	bresenham(t_point start, t_point end, t_point *diff, t_point *direction)
{
	diff->x = abs(start.x - end.x);
	diff->y = abs(start.y - end.y);
	if (start.x < end.x)
		direction->x = 1;
	else
		direction->x = -1;
	if (start.y < end.y)
		direction->y = 1;
	else
		direction->y = -1;
}

void	draw_line(t_point start, t_point end, t_data *img)
{
	t_point	diff;
	t_point	direction;
	int		left_over[2];

	bresenham(start, end, &diff, &direction);
	left_over[0] = diff.x - diff.y;
	while (start.x != end.x || start.y != end.y)
	{
		my_mlx_pixel_put(img, start.x, start.y, start.color);
		left_over[1] = left_over[0] * 2;
		if (left_over[1] > -diff.y)
		{
			left_over[0] -= diff.y;
			start.x += direction.x;
		}
		if (left_over[1] < diff.x)
		{
			left_over[0] += diff.x;
			start.y += direction.y;
		}
	}
}

void	allBlack(t_fdf *fdf)
{
	int	x;
	int	y;

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

void	rendering(t_fdf *fdf)
{
	int	i;
	int	j;

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
					dimensions(fdf->map.points[i][j + 1], &fdf->map),
					&fdf->img);
			if (i != fdf->map.y_max - 1)
				draw_line(dimensions(fdf->map.points[i][j], &fdf->map),
					dimensions(fdf->map.points[i + 1][j], &fdf->map),
					&fdf->img);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
}
