/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:38:32 by coder             #+#    #+#             */
/*   Updated: 2022/01/21 12:18:03 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define HEIGHT 1080
# define WIDTH 1920

# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include "./minilibx_macos/mlx.h"
# include <stdio.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_camera
{
	double	zoom;
	float	z_divisor;
	int		x_pos;
	int		y_pos;
}	t_camera;

typedef struct s_map
{
	t_point		**points;
	t_camera	camera;
	int			x_max;
	int			y_max;
}	t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_fdf
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	map;
}	t_fdf;

void	exec_failed(char *s);
t_map	set_map(char **argv);
float	min(int a, int b);
int		ft_hextoi(char *str);
int		x_coordinate(char **line);
void	free_split(char **split);
t_point	dimensions(t_point point, t_map *map);
void	rendering(t_fdf *fdf);

#endif