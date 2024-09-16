/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:02:50 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/16 18:15:46 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_block(t_cub *cub, int i, int j, unsigned int c)
{
	int	bwidth;
	int	bheigth;
	int	a;
	int	b;

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

void	draw_pixels(t_cub *cub, int x[2], int y[2], int delta[2])
{
	int	sign[2];
	int	err[2];

	sign[0] = -1;
	sign[1] = -1;
	if (x[0] < x[1])
		sign[0] = 1;
	if (y[0] < y[1])
		sign[1] = 1;
	err[0] = delta[0] - delta[1];
	while (x[0] != x[1] || y[0] != y[1])
	{
		mlx_put_pixel(cub->img[0], x[0], y[0], 94702);
		err[1] = err[0] * 2;
		if (err[1] > -1 * delta[1])
		{
			err[0] -= delta[1];
			x[0] += sign[0];
		}
		if (err[1] < delta[0])
		{
			err[0] += delta[0];
			y[0] += sign[1];
		}
	}
}

void	draw_line(t_cub *cub, t_point src, t_point dst)
{
	int	x[2];
	int	y[2];
	int	delta[2];

	x[0] = (fixed_to_float(src.x) / src.plane->width) * cub->img[0]->width;
	y[0] = (fixed_to_float(src.y) / src.plane->heigth) * cub->img[0]->height;
	x[1] = (fixed_to_float(dst.x) / dst.plane->width) * cub->img[0]->width;
	y[1] = (fixed_to_float(dst.y) / dst.plane->heigth) * cub->img[0]->height;
	delta[0] = abs(x[1] - x[0]);
	delta[1] = abs(y[1] - y[0]);
	draw_pixels(cub, x, y, delta);
}

void	draw_player(t_cub *cub)
{
	t_point	p[4];
	t_crash	x;

	p[0] = from_h((t_ray){&cub->p->p, cub->p->angle}, double_to_fixed(0.5));
	p[1] = from_h((t_ray){&cub->p->p, normalize(cub->p->angle
				+ int_to_fixed(200))}, double_to_fixed(0.2));
	p[2] = from_h((t_ray){&cub->p->p, normalize(cub->p->angle
				+ int_to_fixed(180))}, double_to_fixed(0.4));
	p[3] = from_h((t_ray){&cub->p->p, normalize(cub->p->angle
				- int_to_fixed(180))}, double_to_fixed(0.4));
	draw_line(cub, p[0], p[2]);
	draw_line(cub, p[0], p[3]);
	draw_line(cub, p[1], p[2]);
	draw_line(cub, p[1], p[3]);
	// for (int i = 0; i < RAY_NBR; i++)
	// {
		x = cast_ray(cub->p->view[0]);
		draw_line(cub, cub->p->p, x.p);
	// }
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
	flood_fill(cub, cub->p->p, 94702, 94702);
}

void	rec_fill(mlx_image_t *img, uint32_t pos[2], uint8_t lim[8], uint32_t col)
{
	uint8_t* pixel;


	if (img && pos[0] < img->width && pos[1] < img->height && pos[0] >=0 && pos[1] >= 0 && col)
	{
		pixel = &img->pixels[(pos[1] * img->width + pos[0]) * sizeof(int32_t)];
		if ((pixel[0] != lim[0] || pixel[1] != lim[1] || pixel[2] != lim[2] || pixel[3] != lim[3]) && (pixel[0] != lim[4] || pixel[1] != lim[5] || pixel[2] != lim[6] || pixel[3] != lim[7]))
		{
			mlx_put_pixel(img, pos[0], pos[1], col);
			rec_fill(img, (uint32_t[2]){pos[0] + 1, pos[1]}, lim, col);
			rec_fill(img, (uint32_t[2]){pos[0] - 1, pos[1]}, lim, col);
			rec_fill(img, (uint32_t[2]){pos[0], pos[1] - 1}, lim, col);
			rec_fill(img, (uint32_t[2]){pos[0], pos[1] + 1}, lim, col);
		}
	}
}
void	flood_fill(t_cub *cub, t_point p, uint32_t limit, uint32_t fill)
{
	uint32_t	pos[2];
	uint8_t	lim[8];
	
	pos[0] = (fixed_to_float(p.x) / p.plane->width) * cub->img[0]->width;
	pos[1] = (fixed_to_float(p.y) / p.plane->heigth) * cub->img[0]->height;
	lim[0] = (uint8_t)(limit >> 24);
	lim[1] = (uint8_t)(limit >> 16);
	lim[2] = (uint8_t)(limit >> 8);
	lim[3] = (uint8_t)(limit & 0xFF);
	lim[4] = (uint8_t)(fill >> 24);
	lim[5] = (uint8_t)(fill >> 16);
	lim[6] = (uint8_t)(fill >> 8);
	lim[7] = (uint8_t)(fill & 0xFF);
	rec_fill(cub->img[0], pos, lim, fill);
}
