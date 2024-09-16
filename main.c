/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:36:45 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/16 21:59:29 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
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
	for (int i = 0; i < RAY_NBR; i++)
	{
		p.view[i].angle = int_to_fixed(390);
		p.view[i].src = &p.p;
	}
	cub.win = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	if (!cub.win)
	{
		write(2, "MLX error\n", 10);
		return (1);
	}
	mlx_set_window_title(cub.win, "Cub3D");
	cub.img[0] = mlx_new_image(cub.win, WIDTH, HEIGHT);
	if (!cub.img[0])
		return (0);
	if (mlx_image_to_window(cub.win, cub.img[0], 0, 0))
		return (0);
	mlx_loop_hook(cub.win, key_hook, &cub);
	mlx_loop(cub.win);
	mlx_terminate(cub.win);
	destroy_plane(cub.map);
	destroy_obj(obj);
}
