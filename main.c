/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:36:45 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/25 10:32:59 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
	mlx_t	*win;
	t_cub	map;

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
	printf("\nMAP TEXTURES:\n\n");
	printf("north: %s\n", map.north);
	printf("east: %s\n", map.east);
	printf("west: %s\n", map.west);
	printf("south: %s\n", map.south);
	printf("floor: %s\n", map.floor);
	printf("ceiling: %s\n", map.ceiling);
	mlx_loop(win);
	mlx_terminate(win);
	destroy_cub(map);
}
