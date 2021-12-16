/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:39 by coder             #+#    #+#             */
/*   Updated: 2021/12/16 20:13:04 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
ft_make_graphic(t_data *img, t_map *map)
{
	while ()
	{
		my_mlx_pixel_put(img, x, y, color);
		i
	}
}
*/
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
	map = get_relief(argv);
	i = 0;
	while(i < map.y_max)
	{
		j = 0;
		while (j < map.x_max)
		{
			//printf("X: %d ",map.cartography[i][j].x);
			//printf("Y: %d ",map.cartography[i][j].y);
			if (map.cartography[i][j].z > 0)
			{
				
				printf("%d ",map.cartography[i][j].z);
				//printf("%d ",map.cartography[i][j].color);
			}
			else
			{
				printf(" %d ",map.cartography[i][j].z);
				//printf("%d ",map.cartography[i][j].color);
			}
			if (map.cartography[i][j].color != 0xffffff)
				printf("%d ",map.cartography[i][j].color);

			//printf("C: %d	",map.cartography[i][j].color);
			j++;	
		}
		i++;
		printf("\n");
	}
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, 
	&img.bit_per_pixel, &img.line_length, &img.endian);
	//ft_make_graphic(&img, &map); // i bims die svenja
	i = 0;
	j = 0;
	while (i < 100)
	{
		my_mlx_pixel_put(&img, 5 + i, 5 + i, 0x00A90BB19);
		i++;
	}
	while (i < 200)
	{
		my_mlx_pixel_put(&img, 5 + i, 5 + i + j, 0x0000FF00);
		i++;
		j += 5;
	}
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx); // need stuff to end function (free etc)
}
