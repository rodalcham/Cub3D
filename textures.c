/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:49:34 by mbankhar          #+#    #+#             */
/*   Updated: 2024/10/03 17:10:37 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_gun(t_object *object)
{
	object->gun_texture = mlx_load_png("textures/gun1.png");
	if (!object->gun_texture)
	{
		write (2, "Error loading gun\n", 28);
		return (1);
	}
	object->gun_image = mlx_texture_to_image(object->mlxpointer,
			object->gun_texture);
	if (!object->gun_image)
	{
		write(1, "Error converting gun tex to img", 32);
		return (1);
	}
	return (0);
}

int	load_textures(t_object *object)
{
	object->east_texture = mlx_load_png(object->east);
	if (!object->east_texture)
	{
		write (2, "Error loading east texture\n", 28);
		return (1);
	}
	object->west_texture = mlx_load_png(object->west);
	if (!object->west_texture)
	{
		write (2, "Error loading west texture\n", 28);
		return (1);
	}
	object->north_texture = mlx_load_png(object->north);
	if (!object->north_texture)
	{
		write (2, "Error loading north texture\n", 29);
		return (1);
	}
	object->south_texture = mlx_load_png(object->south);
	if (!object->south_texture)
	{
		write (2, "Error loading south texture\n", 29);
		return (1);
	}
	return (0);
}

unsigned int	get_color(mlx_texture_t	*img, t_fixed xy[2], t_fixed wh[2])
{
	t_fixed	pos;
	int		ret;
	uint8_t	*temp;
	int		i;

	pos = (f_mult((f_mult(xy[1], wh[1]) >> 16 << 16), wh[0]))
		+ (f_mult(xy[0], wh[0]));
	temp = &img->pixels[pos >> 16 << 2];
	ret = 0;
	i = -1;
	while (++i < 4)
	{
		ret = ret << 8;
		if (temp == 0)
			ret = ret | 0;
		else
			ret = ret | temp[i];
	}
	return (ret);
}

mlx_texture_t	*start_img(t_crash c, t_cub cub, t_fixed wh[2], t_fixed xy[2])
{
	mlx_texture_t	*image;

	if (c.dir == 'N')
		image = cub.wall->north_texture;
	else if (c.dir == 'S')
		image = cub.wall->south_texture;
	else if (c.dir == 'E')
		image = cub.wall->east_texture;
	else
		image = cub.wall->west_texture;
	wh[0] = image->width << 16;
	wh[1] = image->height << 16;
	if (c.dir == 'N' || c.dir == 'S')
		xy[0] = (c.p.x - (c.p.x >> 16 << 16));
	else if (c.dir == 'E' || c.dir == 'W')
		xy[0] = (c.p.y - (c.p.y >> 16 << 16));
	return (image);
}

void	draw_walls(t_crash crash, t_cub cub, int x, t_fixed angle)
{
	int				wall[3];
	int				y;
	mlx_texture_t	*image;
	t_fixed			wh[2];
	t_fixed			xy[2];

	wall[0] = (int)(HEIGHT / (fixed_to_double(crash.distance)
				* cos(fixed_to_double(angle) / 200 * PI)));
	wall[1] = HEIGHT / 2 - wall[0] / 2;
	wall[2] = wall[0] + wall[1];
	image = start_img(crash, cub, wh, xy);
	y = 0;
	while (y < HEIGHT)
	{
		mlx_put_pixel(cub.img[1], x, y, 0);
		if (y >= wall[1] && y < wall[2])
		{
			xy[1] = double_to_fixed((y - wall[1]) / (double)wall[0]);
			mlx_put_pixel(cub.img[1], x, y, get_color(image, xy, wh));
		}
		y++;
	}
}
