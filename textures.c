/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:49:34 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/18 12:45:31 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_object *object)
{
	object->east_texture = mlx_load_png("textures/walls/08.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
	object->west_texture = mlx_load_png("textures/walls/12.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
	object->north_texture = mlx_load_png("textures/walls/30.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
	object->south_texture = mlx_load_png("textures/walls/39.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
}

// void	texture_to_image(t_object *object)
// {
// 	object->east_image = mlx_texture_to_image(object->mlxpointer,
// 			object->east_texture);
// 	if (!object->east_image)
// 		write(1, "Error converting east tex to img", 33);
// 	object->west_image = mlx_texture_to_image(object->mlxpointer,
// 			object->west_texture);
// 	if (!object->west_image)
// 		write(1, "Error converting west tex to img", 33);
// 	object->north_image = mlx_texture_to_image(object->mlxpointer,
// 			object->north_texture);
// 	if (!object->north_image)
// 		write(1, "Error converting north tex to img", 32);
// 	object->south_image = mlx_texture_to_image(object->mlxpointer,
// 			object->south_texture);
// 	if (!object->south_image)
// 		write(1, "Error converting south tex to img", 32);
// }


unsigned int	get_color(mlx_texture_t	*img, t_fixed xy[2], t_fixed wh[2])
{
	t_fixed	pos;
	int	ret;
	uint8_t	*temp;
	int		i;

	pos = (f_mult((f_mult(xy[1] ,wh[1]) >> 16 << 16), wh[0])) + (f_mult(xy[0], wh[0]));
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

void draw_walls(t_crash crash, t_cub cub, int x)
{
	double	corrected_distance = fixed_to_double(crash.distance);
	int		wall_height = (int)(HEIGHT / corrected_distance);
	int		wall_start = HEIGHT / 2 - wall_height / 2;
	int		wall_end = wall_start + wall_height;
	int		y;
	mlx_texture_t	*image;

	y = 0;
	if (crash.dir == 'N')
		image = cub.wall->north_texture;
	else if (crash.dir == 'S')
		image = cub.wall->south_texture;
	else if (crash.dir == 'E')
		image = cub.wall->east_texture;
	else
		image = cub.wall->west_texture;
	if (corrected_distance <= 0)
		corrected_distance = 1;


	t_fixed	wh[2];
	t_fixed	xy[2];
	// t_fixed	ydelta;

	wh[0] = image->width << 16;
	wh[1] = image->height << 16;

	if (crash.dir == 'N' || crash.dir == 'S')
		xy[0] = (crash.p.x - (crash.p.x >> 16 << 16));
	if (crash.dir == 'E' || crash.dir == 'W')
		xy[0] = (crash.p.y - (crash.p.y >> 16 << 16));
	
	// xy[1] = double_to_fixed((0) / (double)wall_height);
	// ydelta = double_to_fixed((1) / (double)wall_height) - xy[1];
	// if (!ydelta)
	// 	ydelta = 1;

	while (y < HEIGHT)
	{
		mlx_put_pixel(cub.img[1], x, y, 0);
		if (y >= wall_start && y < wall_end)
		{
			// printf("%f :: %f\n", fixed_to_double(xy[0]), fixed_to_double(xy[1]));
			xy[1] = double_to_fixed((y - wall_start) / (double)wall_height);
			// mlx_put_pixel(cub.img[1], x, y++, get_color(image, xy, wh));
			mlx_put_pixel(cub.img[1], x, y, get_color(image, xy, wh));
			// xy[1] += ydelta;
		}
		// else
		y++;
	}
}

