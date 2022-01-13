/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_rotations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:22:48 by coder             #+#    #+#             */
/*   Updated: 2022/01/13 19:33:43 by rschleic         ###   ########.fr       */
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
//so all the rotation we implemented isn't used yet?
