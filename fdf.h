/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:38:32 by coder             #+#    #+#             */
/*   Updated: 2022/01/19 22:09:18 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H
#define HEIGHT 1080
#define WIDTH 1920

#include "./gnl/get_next_line.h"
#include "./libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
//need to create a function for those

typedef struct s_point
{
	int x;
	int y;
	int z;
	int color;
} t_point;

typedef struct s_camera
{
	int    zoom;
	double alpha;
	double beta;
	double gamma;
	float  z_divisor;
	int    x_pos;
	int    y_pos;
} t_camera;

typedef struct s_map
{
	t_point **points;
	t_camera  camera;
	int       x_max;
	int       y_max;
} t_map;

typedef struct s_data
{
	void *img;
	char *addr;
	int   bit_per_pixel;
	int   line_length;
	int   endian;
} t_data;

typedef struct s_fdf
{
	void * mlx;
	void * mlx_win;
	t_data img;
	t_map  map;
} t_fdf;

int     no_valid_input(char **argv);
t_map   set_map(char **argv);
void    draw_line(t_point start, t_point end, t_data *img);
t_point dimensions(t_point point, t_map *map);
void    rotate_x(int *z, int *y, double rotation);
void    rotate_y(int *x, int *z, double rotation);
void    rotate_z(int *x, int *y, double rotation);
int     ft_hextoi(char *str);
int     x_coordinate(char **line);
int     change_camera_zdiv(int key, t_fdf *fdf);
void    rendering(t_fdf *fdf);
void    allBlack(t_fdf *fdf);

#endif