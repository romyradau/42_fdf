/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:39:39 by coder             #+#    #+#             */
/*   Updated: 2022/01/21 13:09:28 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exec_failed(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

int	no_valid_input(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	if (!ft_strnstr(&argv[1][ft_strlen(argv[1]) - ft_strlen(".fdf")],
		".fdf", ft_strlen(".fdf")))
		return (1);
	return (0);
}

int	key_impl(int key, t_fdf *fdf)
{
	if (key == 78)
		fdf->map.camera.z_divisor *= 1.1;
	else if (key == 69 && (fdf->map.camera.z_divisor * 0.8 > 0))
		fdf->map.camera.z_divisor *= 0.8;
	else if (key == 126)
		fdf->map.camera.zoom *= 2;
	else if (key == 125)
		fdf->map.camera.zoom *= 0.5;
	else if (key == 2)
		fdf->map.camera.x_pos += WIDTH / 10;
	else if (key == 0)
		fdf->map.camera.x_pos -= WIDTH / 10;
	else if (key == 1)
		fdf->map.camera.y_pos += HEIGHT / 10;
	else if (key == 13)
		fdf->map.camera.y_pos -= HEIGHT / 10;
	else if (key == 53)
		exit(0);
	rendering(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2 || no_valid_input(argv))
		exec_failed("ERROR: incorrect parameters");
	fdf.map = set_map(argv);
	fdf.mlx = mlx_init();
	if (fdf.mlx == NULL)
		exec_failed("ERROR: mlx_init failed");
	fdf.mlx_win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "Happy Valentines :)");
	if (fdf.mlx_win == NULL)
		exec_failed("ERROR: mlx_win failed");
	fdf.img.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (fdf.img.img == NULL)
		exec_failed("ERROR: mlx_img failed");
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bit_per_pixel,
			&fdf.img.line_length, &fdf.img.endian);
	rendering(&fdf);
	mlx_key_hook(fdf.mlx_win, key_impl, &fdf);
	mlx_loop(fdf.mlx);
}
