/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_rotations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:22:48 by coder             #+#    #+#             */
/*   Updated: 2021/12/24 17:50:10 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void rotate_x(int *z, int *y, double rotation) {
    const int tmp = *y;
​
    *y = (int)(tmp * cos(rotation) + *z * sin(rotation));
    *z = (int)(-tmp * sin(rotation) + *z * cos(rotation));
}
​
void rotate_y(int *x, int *z, double rotation) {
    const int tmp = *x;
​
    *x = (int)(tmp * cos(rotation) + *z * sin(rotation));
    *z = (int)(-tmp * sin(rotation) + *z * cos(rotation));
}
​
void rotate_z(int *x, int *y, double rotation) {
    const int tmp = *x;
    const int tmp2 = *y;
​
    *x = (int)(tmp * cos(rotation) - tmp2 * sin(rotation));
    *y = (int)(tmp * sin(rotation) + tmp2 * cos(rotation));
}

//do i need to make them static?
//static allows use only in file