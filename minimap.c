/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:23:50 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/12 16:51:44 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_block(t_cub *cub, int i, int j, unsigned int c)
{
	int bwidth;
	int bheigth;
	int	a;
	int b;
	
	bwidth = cub->img[0]->width / cub->map->width;
	bheigth = cub->img[0]->height / cub->map->heigth;
	b = bheigth * i;
	while (b < (bheigth * (i + 1)))
	{
		a = bwidth * j;
		while (a < (bwidth * (j + 1)))
		{
			mlx_put_pixel(cub->img[0], a, b, c);
			a++;
		}
		b++;
	}
}

// void	draw_player(t_cub *cub)
// {
// 	int bwidth;
// 	int bheigth;
// 	mlx_texture_t	*files[8];

// 	bwidth = cub->img[1]->width / cub->map->width;
// 	bheigth = cub->img[1]->height / cub->map->heigth;
// 	files[0] = mlx_load_png("./textures/Cursor/r.png");
// 	files[1] = mlx_load_png("./textures/Cursor/tr.png");
// 	files[2] = mlx_load_png("./textures/Cursor/t.png");
// 	files[3] = mlx_load_png("./textures/Cursor/tl.png");
// 	files[4] = mlx_load_png("./textures/Cursor/l.png");
// 	files[5] = mlx_load_png("./textures/Cursor/bl.png");
// 	files[6] = mlx_load_png("./textures/Cursor/b.png");
// 	files[7] = mlx_load_png("./textures/Cursor/br.png");
// 	cub->img[1] = mlx_texture_to_image(cub->win, files[0]);
// }

void	draw_mini(t_cub	*cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->map->heigth)
	{
		j = -1;
		while (++j < cub->map->width)
		{
			if (cub->map->grid[j][i])
				draw_block(cub, i, j, 42424242);
			else
				draw_block(cub, i, j, 42);
		}
	}
	draw_block(cub, fixed_to_int(cub->p->p.y), fixed_to_int(cub->p->p.x), 56232356);
}
