/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_D_to2_D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:15:23 by coder             #+#    #+#             */
/*   Updated: 2021/12/24 17:44:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

t_point dimensions(t_point point, t_map *map) {
    point.x *= map->camera.zoom;
    point.y *= map->camera.zoom;
    point.z *= map->camera.zoom / map->camera.z_divisor;
    point.x -= (map->x_max * map->camera.zoom) / 2;
    point.y -= (map->y_max * map->camera.zoom) / 2;
    rotate_x(&(point.z), &(point.y), map->camera.alpha);
    rotate_y(&(point.x), &(point.z), map->camera.beta);
    rotate_z(&(point.x), &(point.y), map->camera.gamma);
​
    point.x += WIDTH / 2 + map->camera.x_pos;
    point.y += (HEIGHT + map->y_max * map->camera.zoom) / 2 + map->camera.y_pos;
​
    return point;
}
//needs to be applied only once
//bc