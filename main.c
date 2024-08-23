/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:36:45 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/30 11:37:13 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
	mlx_t		*win;
	mlx_image_t	*img;
	t_cub		map;
	t_player	p;

	if (cub_init(&map, "map.cub") < 0)
	{
		write(2, "Invalid map\n", 12);
		return (1);
	}
	win = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	if (!win)
	{
		write(2, "MLX error\n", 10);
		return (1);
	}
	img = mlx_new_image(win, WIDTH, HEIGHT);
	if (!img)
	{
		write(2, "MLX error\n", 10);
		return (1);
	}
	if (mlx_image_to_window(win, img, 0 ,0) < 0)
	{
		write(2, "MLX error\n", 10);
		return (1);
	}
	p.x = 5;
	p.y = 5;
	p.delta = 1;
	// validate map walls and paths, colours
	// set player pos
	// cast rays
	draw_fov(p, map, win, img);
	mlx_loop(win);
	mlx_terminate(win);
	destroy_cub(map);
}
