/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:36:45 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/17 13:48:18 by rchavez          ###   ########.fr       */
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
	// normalize()
	if (obj_init(&obj, &cub, "map.cub") < 0)
	{
		write(2, "Invalid map\n", 12);
		return (1);
	}
	p.p.x = 358050;
	p.p.y = 788876;
	p.angle = 22544384;
	// p.angle = int_to_fixed(190);
	t_fixed delta = f_div(int_to_fixed(FOV), int_to_fixed(RAY_NBR));
	for (int i = 0; i < RAY_NBR; i++)
	{
		p.view[i].angle = normalize(p.angle + f_mult(delta, int_to_fixed(i - RAY_NBR / 2)));
		p.view[i].src = &p.p;
	}
	cub.win = mlx_init(WIDTH, HEIGHT , "Cub3D", 1);
	if (!cub.win)
	{
		write(2, "MLX error\n", 10);
		return (1);
	}
	mlx_set_window_title(cub.win, "Cub3D");
	cub.img[0] = mlx_new_image(cub.win, HEIGHT/4, HEIGHT/4);
	cub.img[1] = mlx_new_image(cub.win, HEIGHT, WIDTH);
	if (!cub.img[0])
		return (0);
	if (mlx_image_to_window(cub.win, cub.img[0], 0, 0))
		return (0);
	if (mlx_image_to_window(cub.win, cub.img[1], 0, 0))
		return (0);
	mlx_loop_hook(cub.win, key_hook, &cub);
	mlx_loop(cub.win);
	mlx_terminate(cub.win);
	destroy_plane(cub.map);
	destroy_obj(obj);
}
