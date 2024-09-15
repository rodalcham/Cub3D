/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:23:50 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/15 13:43:02 by mbankhar         ###   ########.fr       */
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


// void	draw_line(t_cub *cub, t_point src, t_point dst)
// {
// 	int	srcx;
// 	int	srcy;
// 	int	dstx;
// 	int	dsty;

// 	srcx = (fixed_to_float(src.x) / src.plane->width) * (cub->img[0]->width);
// 	srcy = (fixed_to_float(src.y) / src.plane->heigth) * (cub->img[0]->height);
// 	dstx = (fixed_to_float(dst.x) / dst.plane->width) * (cub->img[0]->width);
// 	dsty = (fixed_to_float(dst.y) / dst.plane->heigth) * (cub->img[0]->height);
// 	while (srcy != dsty || srcx != dstx)
// 	{
// 		mlx_put_pixel(cub->img[0], srcx, srcy, 94702);
// 		if (srcx < dstx)
// 			srcx++;
// 		else if (srcx > dstx)
// 			srcx--;
// 		if (srcy < dsty)
// 			srcy++;
// 		else if (srcy > dsty)
// 			srcy--;
// 	}
// }

void draw_line(t_cub *cub, t_point src, t_point dst)
{
	int x0 = (fixed_to_float(src.x) / src.plane->width) * cub->img[0]->width;
	int y0 = (fixed_to_float(src.y) / src.plane->heigth) * cub->img[0]->height;
	int x1 = (fixed_to_float(dst.x) / dst.plane->width) * cub->img[0]->width;
	int y1 = (fixed_to_float(dst.y) / dst.plane->heigth) * cub->img[0]->height;
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

    while (1)
    {
        mlx_put_pixel(cub->img[0], x0, y0, 94702); // Color of the line
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}



// void	draw_player(t_cub *cub)
// {
// 	int bwidth;
// 	int bheigth;
// 	int	a;
// 	int b;
	
// 	bwidth = cub->img[0]->width / cub->map->width;
// 	bheigth = cub->img[0]->height / cub->map->heigth;
// 	b = fixed_to_float(cub->p->p.y) * bheigth;
// 	while (b < fixed_to_float(cub->p->p.y) * bheigth + (bheigth / 2))
// 	{
// 		a = fixed_to_float(cub->p->p.x) * bwidth;
// 		while (a < fixed_to_float(cub->p->p.x) * bwidth + (bwidth / 2))
// 		{
// 			mlx_put_pixel(cub->img[0], a, b, 4242);
// 			a++;
// 		}
// 		b++;
// 	}
// 	draw_line(cub, cub->p->p, from_h((t_ray){&cub->p->p, cub->p->angle}, int_to_fixed(1)));
// }
void	draw_player(t_cub *cub)
{
	int	bwidth;
	int	bheigth;
	int	px;
	int	py;
	int	radius;
	int	y;
	int	x;

	radius = 3;
	bwidth = cub->img[0]->width / cub->map->width;
	bheigth = cub->img[0]->height / cub->map->heigth;
	px = fixed_to_float(cub->p->p.x) * bwidth;
	py = fixed_to_float(cub->p->p.y) * bheigth;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_put_pixel(cub->img[0], px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
	t_point player_position = cub->p->p;
	t_point direction_point = from_h((t_ray){&cub->p->p, cub->p->angle}, int_to_fixed(2));
	draw_line(cub, player_position, direction_point);
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


