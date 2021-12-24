/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:38:32 by coder             #+#    #+#             */
/*   Updated: 2021/12/24 17:40:54 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define HEIGHT 1080
# define WIDTH 1920

# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <mlx_int.h>
# include <math.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

# define min(a,b) (((a)<(b))?(a):(b))
# define max(a,b) (((a)>(b))?(a):(b))

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct	s_camera {
	int zoom;
    double alpha;
    double beta;
    double gamma;
    float z_divisor;
    int x_pos;
    int y_pos;
}				t_camera;
		
typedef struct s_map {
	t_point	**points;
	t_camera	camera;
	int			x_max;
	int			y_max;
}				t_map;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//do we still need this?

int		no_valid_input(char **argv);
t_map	get_map_dimensions(char **argv);
t_map	get_relief(char **argv);
void	draw_line(t_point start, t_point end, t_data *img);
t_point dimensions(t_point point, t_map *map);
void rotate_x(int *z, int *y, double rotation);
void rotate_y(int *x, int *z, double rotation);
void rotate_z(int *x, int *y, double rotation);


#endif