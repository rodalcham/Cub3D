/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:36:45 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/12 11:20:05 by rchavez          ###   ########.fr       */
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
	printf("%s\n", obj.ceiling);
	printf("%s\n", obj.floor);
	printf("%s\n", obj.north);
	printf("%s\n", obj.south);
	printf("%s\n", obj.east);
	printf("%s\n", obj.west);
	printf("%i\n", cub.map->width);
	printf("%i\n", cub.map->heigth);
	printf("Player location: x: %i, y: %i, angle: %i\n", fixed_to_int(p.p.x), fixed_to_int(p.p.y), fixed_to_int(p.angle));
	for (int i = 0; i < cub.map->heigth; i++)
	{
		for (int j = 0; j < cub.map->width; j++)
		{
			if (cub.map->grid[j][i])
				printf("1");
			else
				printf("0");
		}
		printf("\n");
	}
	cub.win = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	if (!cub.win)
	{
		write(2, "MLX error\n", 10);
		return (1);
	}
	mlx_key_hook(cub.win, key_hook, &cub);
	mlx_loop(cub.win);
	mlx_terminate(cub.win);
	destroy_obj(obj);
}
