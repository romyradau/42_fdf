/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_rotations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:22:48 by coder             #+#    #+#             */
/*   Updated: 2022/01/19 22:23:01 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotate_x(int *z, int *y, double rotation)
{
	int tmp = *y;

	*y = (int) (tmp * cos(rotation) + *z * sin(rotation));
	*z = (int) (-tmp * sin(rotation) + *z * cos(rotation));
}

void rotate_y(int *x, int *z, double rotation)
{
	int tmp = *x;

	*x = (int) (tmp * cos(rotation) + *z * sin(rotation));
	*z = (int) (-tmp * sin(rotation) + *z * cos(rotation));
}

void rotate_z(int *x, int *y, double rotation)
{
	int tmp = *x;
	int tmp2 = *y;

	*x = (int) (tmp * cos(rotation) - tmp2 * sin(rotation));
	*y = (int) (tmp * sin(rotation) + tmp2 * cos(rotation));
}

/*
t_point dimensions(t_point point, t_map *map)
{
	point.x *= map->camera.zoom;
	point.y *= map->camera.zoom;
	// TODO maybe key bindings to fit on any window
	point.z *= map->camera.zoom / map->camera.z_divisor;
	//scaling
	//zoom is for multiplying the points by a fixed value
	//what happens here exactly?
	point.x -= (map->x_max * map->camera.zoom) / 2;
	point.y -= (map->y_max * map->camera.zoom) / 2;
	//center the points, to draw from the middle
	//and than what happens here?
	// rotate_x(&(point.z), &(point.y), map->camera.alpha);
	// rotate_y(&(point.x), &(point.z), map->camera.beta);
	// rotate_z(&(point.x), &(point.y), map->camera.gamma);
	// z rotation to get rid of it
	//if i comment it out nothing bad happens
	iso_projection(&(point.x), &(point.y), point.z);
	// z no change bc it just gets ignored anyways
	point.x += WIDTH / 2 + map->camera.x_pos;
	point.y += HEIGHT / 2 + map->camera.y_pos;
	return point;
}
*/