/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:02:50 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/21 17:49:48 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_player(t_cub *cub, int map)
{
	t_point	p[4];
	t_crash	x;
	int		i;

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
	i = -1;
	while (++i < RAY_NBR)
	{
		x = cast_ray(cub->p->view[i]);
		if (map)
			draw_line(cub, cub->p->p, x.p);
		draw_walls(x, *cub, i, cub->p->view[i].angle - cub->p->angle);
	}
}

void	draw_mini(t_cub	*cub)
{
	int	map;
	
	if (mlx_is_key_down(cub->win, MLX_KEY_M))
	{
		map = 1;
		static_map(cub);
	}
	else
	{
		map = 0;
		minimap(cub);
	}
	draw_player(cub, map);
}
