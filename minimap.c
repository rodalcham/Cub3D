/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:23:50 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/14 14:25:01 by rchavez          ###   ########.fr       */
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
// 	files[0] = mlx_load_png("./textures/Curswor/r.png");
// 	files[1] = mlx_load_png("./textures/Cursor/tr.png");
// 	files[2] = mlx_load_png("./textures/Cursor/t.png");
// 	files[3] = mlx_load_png("./textures/Cursor/tl.png");
// 	files[4] = mlx_load_png("./textures/Cursor/l.png");
// 	files[5] = mlx_load_png("./textures/Cursor/bl.png");
// 	files[6] = mlx_load_png("./textures/Cursor/b.png");
// 	files[7] = mlx_load_png("./textures/Cursor/br.png");
// 	cub->img[1] = mlx_texture_to_image(cub->win, files[0]);
// }


void	draw_line(t_cub *cub, t_point src, t_point dst)
{
	int	srcx;
	int	srcy;
	int	dstx;
	int	dsty;

	srcx = (fixed_to_float(src.x) / src.plane->width) * (cub->img[0]->width);
	srcy = (fixed_to_float(src.y) / src.plane->heigth) * (cub->img[0]->height);
	dstx = (fixed_to_float(dst.x) / dst.plane->width) * (cub->img[0]->width);
	dsty = (fixed_to_float(dst.y) / dst.plane->heigth) * (cub->img[0]->height);
	while (srcy != dsty || srcx != dstx)
	{
		mlx_put_pixel(cub->img[0], srcx, srcy, 94702);
		if (srcx < dstx)
			srcx++;
		else if (srcx > dstx)
			srcx--;
		if (srcy < dsty)
			srcy++;
		else if (srcy > dsty)
			srcy--;
	}
}

void	draw_player(t_cub *cub)
{
	int bwidth;
	int bheigth;
	int	a;
	int b;
	
	bwidth = cub->img[0]->width / cub->map->width;
	bheigth = cub->img[0]->height / cub->map->heigth;
	b = fixed_to_float(cub->p->p.y) * bheigth;
	while (b < fixed_to_float(cub->p->p.y) * bheigth + (bheigth / 2))
	{
		a = fixed_to_float(cub->p->p.x) * bwidth;
		while (a < fixed_to_float(cub->p->p.x) * bwidth + (bwidth / 2))
		{
			mlx_put_pixel(cub->img[0], a, b, 4242);
			a++;
		}
		b++;
	}
	draw_line(cub, cub->p->p, from_h((t_ray){&cub->p->p, cub->p->angle}, int_to_fixed(1)));
}

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
	draw_player(cub);
}
