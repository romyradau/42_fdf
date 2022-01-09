/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_3dto2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:15:23 by coder             #+#    #+#             */
/*   Updated: 2021/12/26 13:12:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void iso_projection(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;
	
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

t_point dimensions(t_point point, t_map *map) {
    point.x *= map->camera.zoom;
    point.y *= map->camera.zoom;
    point.z *= map->camera.zoom / map->camera.z_divisor;
    point.x -= (map->x_max * map->camera.zoom) / 2;
    point.y -= (map->y_max * map->camera.zoom) / 2;
    rotate_x(&(point.z), &(point.y), map->camera.alpha);
    rotate_y(&(point.x), &(point.z), map->camera.beta);
    rotate_z(&(point.x), &(point.y), map->camera.gamma);
	//z rotation to get rid of ot
	iso_projection(&(point.x), &(point.y), point.z);
	//z no change bc it just gets ignored anyways
    point.x += WIDTH / 2 + map->camera.x_pos;
    point.y += (HEIGHT + map->y_max * map->camera.zoom) / 2 + map->camera.y_pos;
    return point;
}
//needs to be applied only once
//bc