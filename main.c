/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:36:45 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/19 11:20:50 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_cub		cub;
	t_player	p;
	t_object	obj;

	cub.wall = &obj;
	cub.p = &p;
	if (obj_init(&obj, &cub, "map.cub") < 0)
	{
		write(2, "Invalid map\n", 12);
		return (1);
	}
	cub.win = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	if (!cub.win)
	{
		write(2, "MLX error\n", 10);
		return (1);
	}
	load_textures(cub.wall);
	mlx_set_window_title(cub.win, "Cub3D");
	cub.img[0] = mlx_new_image(cub.win, HEIGHT / 4, HEIGHT / 4);
	cub.img[1] = mlx_new_image(cub.win, WIDTH, HEIGHT);
	if (!cub.img[0])
		return (0);
	if (mlx_image_to_window(cub.win, cub.img[1], 0, 0))
		return (0);
	if (mlx_image_to_window(cub.win, cub.img[0], 0, 0))
		return (0);
	mlx_loop_hook(cub.win, key_hook, &cub);
	mlx_loop(cub.win);
	mlx_terminate(cub.win);
	destroy_plane(cub.map);
	destroy_obj(obj);
}
