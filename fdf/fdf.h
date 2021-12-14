/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:38:32 by coder             #+#    #+#             */
/*   Updated: 2021/12/11 16:38:34 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <mlx_int.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

typedef struct s_relief {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_relief;

typedef struct s_map {
	t_relief	**cartography;
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

int		no_valid_input(char **argv);
t_map	get_x_y_coordinates(char **argv);
t_map	get_relief(char **argv);



#endif